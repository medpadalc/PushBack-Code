#include "logger.hpp"

logging::Logger::Logger() {
    view = rd_view_create("Logger");
    lv_obj_set_style_bg_color(view->obj, color_bg, 0);

    output_container = lv_obj_create(view->obj);
    lv_obj_set_width(output_container, lv_pct(100));
    lv_obj_set_height(output_container, lv_pct(100));
    lv_obj_align(output_container, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(output_container, &style_transp, 0);

    output = lv_label_create(output_container);
    lv_obj_set_height(output, LV_SIZE_CONTENT);
    lv_obj_add_style(output, &style_transp, 0);
    lv_obj_add_style(output, &style_text_mono, 0);
    lv_label_set_recolor(output, true);
    lv_label_set_long_mode(output, LV_LABEL_LONG_WRAP);
}

void logging::Logger::print(std::string str) {
    stream << str;
    if (output) lv_label_set_text(output, stream.str().c_str());
    lv_obj_scroll_to_y(output_container, LV_COORD_MAX, LV_ANIM_OFF);
}

void logging::Logger::println(std::string str) {
    print(str + "\n");
}

void logging::Logger::sendMessage(const lemlib::Message& message) {
    if (message.level == lemlib::Level::ERROR || message.level == lemlib::Level::FATAL) {
        rd_view_alert(view, fmt::format("[{}] {}", message.level, message.message).c_str());
    }
    printfmt("[{}] {}\n", message.level, message.message);
}

std::shared_ptr<logging::Logger> logging::getLogger() {
    static std::shared_ptr<logging::Logger> logger = std::make_shared<logging::Logger>();
    return logger;
}
