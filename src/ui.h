#ifndef __UI_H__
#define __UI_H__

enum _status {on, off, not_configured, disconnected, connected, error};

struct st_ui_data {
    _status wifi_status;
    _status cloud_status;
    _status ntp_status;
};

extern st_ui_data ui_data;

void ui_init();
void ui_update(bool force_update = false);

#endif
