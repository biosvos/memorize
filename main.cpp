#include "adapter/object_box_repository.h"
#include "adapter/forgetting_curve.h"
#include "infra/gtk_ui.h"
#include "usecase/usecase_impl.h"

int main() {
    auto repository = std::make_shared<ObjectBoxRepository>();
    auto forgetting_curve = std::make_shared<ForgettingCurve>();
    auto usecase = std::make_shared<UsecaseImpl>(repository, forgetting_curve);
    auto app = std::make_shared<GtkUi>(usecase);
    app->Run();
    return 0;
}