#ifndef ROLACONTROLLER_H
#define ROLACONTROLLER_H

#include "src/gui/dialog/FormatEditRola.h"
#include "include/database/models/Rola.h"

class RolaController {
public:
    RolaController(FormatEditRola& view, Rola& model);

private:
    FormatEditRola& m_View;
    Rola& m_Model;

    void on_dialog_response(int response);
};

#endif // ROLACONTROLLER_H
