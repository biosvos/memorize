#include <argumentum/argparse.h>

#include "adapter/object_box_repository.h"
#include "adapter/forgetting_curve.h"
#include "usecase/usecase_impl.h"
#include "infra/ui.h"
#include "infra/ftx.h"

class CliOptions : public argumentum::CommandOptions {
public:
    explicit CliOptions(const std::string_view &name) :
            CommandOptions(name) {}

    void execute(const argumentum::ParseResult &result) override {
        auto repository = std::make_shared<ObjectBoxRepository>();
        auto forgetting_curve = std::make_shared<ForgettingCurve>();
        auto usecase = std::make_shared<UsecaseImpl>(repository, forgetting_curve);
        auto app = std::make_shared<Ftx>(usecase);
        app->Run();
    }
};

int main(int argc, char **argv) {
    auto parser = argumentum::argument_parser{};
    auto params = parser.params();

    parser.config().program(argv[0]).description("Accumulator");
    params.add_command<CliOptions>("cli").help("cli");

    const argumentum::ParseResult &result = parser.parse_args(argc, argv, 1);
    if (!result) {
        return 1;
    }

    result.commands.back()->execute(result);
    return 0;
}