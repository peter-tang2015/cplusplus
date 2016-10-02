// MaxValueOfStockExchange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ctime>
#include <iostream>
#include <unordered_map>

static size_t foundCounts = 0;

double GetPredictedSharePrice(size_t day)
{
    const double prices[] = { 90.0, 80.0, 40.0, 30.0 };

    return prices[day];
}

double GetEffectOnSharePriceFromLargeSales(size_t shares)
{
    if (shares == 0) {
        return 0;
    }

    if (shares <= 40000) {
        return 1;
    }
    else {
        return 20;
    }

}

struct StockExchangeKey {
    size_t cur_day;
    size_t remaining_share;
    double accumalted_price_discount;

    bool operator() (const StockExchangeKey& right) const {
        return cur_day == right.cur_day &&
               remaining_share == right.remaining_share &&
               accumalted_price_discount == right.accumalted_price_discount;
    }
};

struct StockExchangeKey_Hash {
    size_t operator() (const StockExchangeKey& key) const {
        return std::hash<size_t>()(key.cur_day) ^
            std::hash<size_t>()(key.remaining_share) ^
            std::hash<double>()(key.accumalted_price_discount);
    }

    bool operator() (const StockExchangeKey& k1, const StockExchangeKey& k2) const {
        return k1.operator()(k2);
    }
};
typedef std::unordered_map<StockExchangeKey, double, StockExchangeKey_Hash, StockExchangeKey_Hash> StockExchangeHashMap;

double StrategyForSale(size_t duration_days,
                       size_t minimal_quantity_for_sale,
                       size_t remaining_shares,
                       size_t cur_day,
                       double accumulated_price_effect_over_sale,
                       StockExchangeHashMap& SE_Cache)
{
    if (remaining_shares == 0) {
        return 0;
    }

    double priceOfDay = GetPredictedSharePrice(cur_day);
    if ((cur_day + 1) == duration_days) {
        // At the last day, sell whatever in hand with
        // whatever price to cash in
        double priceForSale = priceOfDay - accumulated_price_effect_over_sale -
            GetEffectOnSharePriceFromLargeSales(remaining_shares);
        if (priceForSale > 0) {
            return priceForSale * remaining_shares;
        }
        // should not hit here because the share price must be > 0
        return 0;
    }
    
    StockExchangeKey key{ cur_day, remaining_shares, accumulated_price_effect_over_sale };
    {
        StockExchangeHashMap::const_iterator constIt = SE_Cache.find(key);
        if (constIt != SE_Cache.end()) {
            ++foundCounts;
            return constIt->second;
        }
    }

    double maxShareValue = 0;
    double shareValue;
    double accumPriceEffectOverSale;
    for (size_t sharesForSale = 0; sharesForSale <= remaining_shares; sharesForSale += minimal_quantity_for_sale) {
        accumPriceEffectOverSale = accumulated_price_effect_over_sale +
            GetEffectOnSharePriceFromLargeSales(sharesForSale);
        // values of selling the number of "shareForSale" shares
        shareValue = (priceOfDay - accumPriceEffectOverSale) * sharesForSale;
        // add up the values of rest of share values
        shareValue += StrategyForSale(duration_days,
                                      minimal_quantity_for_sale,
                                      remaining_shares - sharesForSale,
                                      cur_day + 1,
                                      accumPriceEffectOverSale,
                                      SE_Cache);
        if (shareValue > maxShareValue) {
            maxShareValue = shareValue;
        }
    }

    SE_Cache.insert(std::make_pair(key, maxShareValue));

    // std::cout << "maxShareValue: " << maxShareValue << std::endl;

    return maxShareValue;
}

double MaxValueOfStockExchange(size_t days, size_t minimalQuantityForSale, size_t shares)
{
    StockExchangeHashMap seCache;
    return StrategyForSale(days, minimalQuantityForSale,shares, 0, 0.0, seCache);
}


int _tmain(int argc, _TCHAR* argv[])
{
    foundCounts = 0;
    clock_t startTime = clock();
    double maxValue = MaxValueOfStockExchange(3, 100, 100000); // 7.42e+6
    std::cout << "N = 3, step = 100, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    foundCounts = 0;
    startTime = clock();
    maxValue = MaxValueOfStockExchange(3, 10, 100000);
    std::cout << "N = 3, step = 10, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    foundCounts = 0;
    startTime = clock();
    maxValue = MaxValueOfStockExchange(3, 1, 100000);
    std::cout << "N = 3, step = 1, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    foundCounts = 0;
    startTime = clock();
    maxValue = MaxValueOfStockExchange(4, 100, 100000);
    std::cout << "N = 4, step = 100, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    foundCounts = 0;
    startTime = clock();
    maxValue = MaxValueOfStockExchange(4, 10, 100000);
    std::cout << "N = 4, step = 10, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    foundCounts = 0;
    startTime = clock();
    maxValue = MaxValueOfStockExchange(4, 1, 100000);
    std::cout << "N = 4, step = 1, X = 100000: " << double(clock() - startTime) / (double)CLOCKS_PER_SEC << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "foundCounts: " << foundCounts;

    return 0;
}

// http://math.stackexchange.com/questions/796812/dynamic-programming-stock-exercise