//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_USECASE_H
#define MEMORIZE_USECASE_H

template<typename IN, typename OUT>
struct Usecase {
    class IRequester {
    public:
        virtual ~IRequester() = default;

        virtual void Request(const IN &req) = 0;
    };

    class IResponder {
    public:
        virtual ~IResponder() = default;

        virtual void Response(const OUT &rsp) = 0;
    };
};

#endif //MEMORIZE_USECASE_H
