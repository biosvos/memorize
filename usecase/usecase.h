//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_USECASE_H
#define MEMORIZE_USECASE_H

#include <system_error>

template<typename IN, typename OUT>
struct Usecase {
    class IRequester {
    public:
        virtual ~IRequester() = default;

        virtual std::error_code Request(const IN &req) = 0;
    };

    class IResponder {
    public:
        virtual ~IResponder() = default;

        virtual std::error_code Response(const OUT &rsp) = 0;
    };
};

#endif //MEMORIZE_USECASE_H
