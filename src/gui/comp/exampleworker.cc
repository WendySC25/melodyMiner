/* gtkmm example Copyright (C) 2013 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "exampleworker.h"
#include "examplewindow.h"
#include <sstream>
#include <chrono>

ExampleWorker::ExampleWorker() :
  m_Mutex(),
  m_shall_stop(false),
  m_has_stopped(false),
  m_fraction_done(0.0),
  m_message()
{
}

void ExampleWorker::get_data(double* fraction_done, Glib::ustring* message) const {
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (fraction_done)
    *fraction_done = m_fraction_done;

  if (message)
    *message = m_message;
}

void ExampleWorker::stop_work(){
  std::lock_guard<std::mutex> lock(m_Mutex);
  m_shall_stop = true;
}

bool ExampleWorker::has_stopped() const {
  std::lock_guard<std::mutex> lock(m_Mutex);
  return m_has_stopped;
}

void ExampleWorker::do_work(ExampleWindow* caller) {
  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_has_stopped = false;
    m_fraction_done = 0.0;
    m_message = "";
  } 

  //work

  // Simulate a long calculation.
  for (int i = 0; ; ++i) {

    {
      std::lock_guard<std::mutex> lock(m_Mutex);

      m_fraction_done += 0.01;

      if (i % 4 == 3){
        std::ostringstream ostr;
        ostr << (m_fraction_done * 100.0) << "% done\n";
        m_message += ostr.str();
      }

      if (m_fraction_done >= 1.0){
        m_message += "Finished";
        break;
      }
      if (m_shall_stop){
        m_message += "Stopped";
        break;
      }
    

    caller->notify();
  }

  {
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_shall_stop = false;
    m_has_stopped = true;
  }

  caller->notify();
}
