#ifndef GTKMM_MELODYMINERWINDOW_H
#define GTKMM_MELODYMINERWINDOW_H

#include <gtkmm.h>
#include <gdkmm.h>
#include <gio/gio.h> 

#include <memory>
#include <array>
#include <iostream>
#include <sstream>

#include "src/gui/RolaDetailview.h"
#include "src/gui/dialog/FormatEditRola.h"
#include "src/gui/dialog/RolaController.h"
#include "src/gui/MinerDialog.h"
#include "include/database/DatabaseUtils.h"



class MelodyMinerWindow : public Gtk::Window{
    public:
        MelodyMinerWindow(const std::string& dbPath);
        ~MelodyMinerWindow() override;
        Gtk::Window* get_window();

    protected:
        class ModelColumns;
        Glib::RefPtr<Gtk::Builder> builder;

        void on_button_quit();
        void on_item_activated(unsigned int position);
        void on_selection_changed();
        void on_setup_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
        void on_bind_listitem(const Glib::RefPtr<Gtk::ListItem>& list_item);
        int on_model_sort(const Glib::RefPtr<const ModelColumns>& a, const Glib::RefPtr<const ModelColumns>& b);
        void fillModelFromRolas(const std::vector<Rola>& rolas);
        void updateModelFromRolas(const std::vector<Rola>& rolas);
        void add_entry(const std::string& filename, const Glib::ustring& description, const Rola& rola);

        void on_search_entry_changed();
        void on_search_button_clicked();
        
        void clearModel();

        void on_select_file_button_clicked();
        void on_folder_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog);
        void on_mining_finished();
        
        Glib::RefPtr<Gio::ListStore<ModelColumns>> m_data_model;
        Glib::RefPtr<Gtk::SingleSelection> m_selection_model;
        Glib::RefPtr<Gtk::SignalListItemFactory> m_factory;

        Gtk::Window* m_MainWindow;
        Gtk::ScrolledWindow* m_ScrolledWindow;
        Gtk::GridView* m_GridView;
        Gtk::Box* m_ButtonBox;
        Gtk::Button* m_Button_Quit;
        Gtk::Entry* m_SearchEntry;
        Gtk::Button* m_SearchButton;
        Gtk::Button* m_SelectFileButton;

        Database database;
        RolaDAO rolaDAO;

        class ModelColumns : public Glib::Object{
            public:
                std::string m_filename;
                Glib::ustring m_description;
                Glib::RefPtr<Gdk::Texture> m_texture;

                Rola m_rola;

                static Glib::RefPtr<ModelColumns> create(const std::string& filename,
                    const Glib::ustring& description, const Glib::RefPtr<Gdk::Texture>& texture, const Rola& rola){
                    return Glib::make_refptr_for_instance<ModelColumns>(new ModelColumns(filename, description, texture, rola));
                }

            protected:
                ModelColumns(const std::string& filename, const Glib::ustring& description,
                    const Glib::RefPtr<Gdk::Texture>& texture, const Rola& rola)
                    : m_filename(filename), m_description(description), m_texture(texture), m_rola(rola)
                {}
        }; 
};
        

#endif // GTKMM_MELODYMINERWINDOW_H
