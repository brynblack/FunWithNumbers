#include "stats.hpp"

namespace fwn {
    void fwn::Stats::addStat(const std::string &name) {
        Stat stat { 0 };
        this->stats[name] = stat;
    }

    auto fwn::Stats::getStat(const std::string &name) -> long long {
        return this->stats[name].getValue();
    }

    void fwn::Stats::setStat(const std::string &name, long long value) {
        this->stats[name].setValue(value);
    }

    auto fwn::Stats::Stat::getValue() const -> long long {
        return this->value;
    }

    void fwn::Stats::Stat::setValue(long long value) {
        this->value = value;
    }
} // namespace fwn
