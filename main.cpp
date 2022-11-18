#include "adapter/object_box_repository.h"
#include "adapter/forgetting_curve.h"
#include "usecase/usecase_impl.h"
//#include "infra/gtk_ui.h"
#include "infra/nana_ui.h"

int main() {
    auto repository = std::make_shared<ObjectBoxRepository>();
    auto forgetting_curve = std::make_shared<ForgettingCurve>();
    auto usecase = std::make_shared<UsecaseImpl>(repository, forgetting_curve);
//    auto app = std::make_shared<GtkUi>(usecase);
    auto app = std::make_shared<NanaUi>(usecase);
    app->Run();
    return 0;
}