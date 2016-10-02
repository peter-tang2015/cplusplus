#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <vector>

/*
 * Edit in Visual Studio 2013 and compile with C++11 gcc 4.9.2 and run in UNIX
 */

class CreationException : public std::exception
{
public:
    explicit CreationException(const std::string& who,
                               const std::string& reason)
        : mMsg(who + ": Fail to construct - " + reason)
    {}

    virtual ~CreationException() throw()
    {}

    virtual const char* what() const throw()
    {
        return mMsg.c_str();
    }

private:
    std::string mMsg;
};

namespace MyRandom
{

template<typename EngineType, typename DataType>
class DiscreteRandomNumberGenerator
{
public:
    DiscreteRandomNumberGenerator(const std::vector<DataType>& randomNumbers,
                                  const std::vector<double>& probabilities)
                                    : mRandomeNumbers(randomNumbers),
                                      mDiscreteDist(probabilities.begin(),
                                                    probabilities.end()),
                                      mEngine(mRandomDevice())
    {
        if (randomNumbers.empty()) {
            throw CreationException("DiscreteRandomNumberGenerator",
                                    "randomNumbers.empty()");
        }

        if (probabilities.empty()) {
            throw CreationException("DiscreteRandomNumberGenerator",
                                    "probabilities.empty()");
        }

        if (randomNumbers.size() != probabilities.size()) {
            throw CreationException("DiscreteRandomNumberGenerator",
                                    "randomNumbers.size() != probabilites.size()");
        }
        auto maxProb = probabilities[0];
        for (auto x : probabilities) {
            if (x < 0) {
                throw CreationException("DiscreteRandomNumberGenerator",
                                        "negative value in probabilities");
            }
            if (maxProb < x) {
                maxProb = x;
            }
        }

        if (maxProb <= 0) {
            throw CreationException("DiscreteRandomNumberGenerator",
                                    "no positive value in probabilities");
        }

    }

    ~DiscreteRandomNumberGenerator() = default;

    DiscreteRandomNumberGenerator(
        DiscreteRandomNumberGenerator<EngineType, DataType>&) = delete;

    DiscreteRandomNumberGenerator<EngineType, DataType>& operator=(
        DiscreteRandomNumberGenerator<EngineType, DataType>&) = delete;


    DataType nextNum()
    {
        auto index = mDiscreteDist(mEngine);
        return mRandomeNumbers[index];
    }

private:
    std::random_device mRandomDevice;
    std::discrete_distribution<int> mDiscreteDist;
    EngineType mEngine;
    std::vector<DataType> mRandomeNumbers;
};

#include <cassert>
template<typename EngineType>
void TestCase_GivenLowRepeatAndHighTolerance_ExpectSuccess()
{
    std::vector<int> randomNumbers{ -1, 0, 1, 2, 3, 4, 5 };
    std::vector<double> probabilities{ 0.01, 0.3, 0.58 - 2E-5, 0.1, 0.01, 1E-5, 1E-5 };
    DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);

    std::map<int, size_t> frequencyMap;
    for (auto x : randomNumbers) {
        // initialize as zero, in case that no such number is generated
        frequencyMap[x] = 0;
    }

    auto repeat = 100000;
    for (auto i = 0; i < repeat; ++i) {
        auto rdn = myDRNG.nextNum();
        ++frequencyMap[rdn];
    }

    const double relativeTolerance = 0.2;
    const double probThreshold = 1e-5;
    const double absoluteTolerance = 2 * probThreshold;

    auto it = frequencyMap.begin();
    auto idx = 0;
    double repeatDouble = repeat;
    for (auto prob : probabilities) {
        std::cout << "Random num: " << it->first
            << ", Frequency: " << it->second
            << ", probability expected: " << prob
            << ", probability actual: " << it->second / repeatDouble;
        assert(it->first == randomNumbers[idx]);
        if (prob > probThreshold) {
            std::cout << ", rel diff: " << fabs(prob - it->second / repeatDouble) / prob;
            assert(fabs(prob - it->second / repeatDouble) / prob <= relativeTolerance);
        }
        else {
            std::cout << ", abs diff: " << fabs(prob - it->second / repeatDouble);
            assert(fabs(prob - it->second / repeatDouble) <= absoluteTolerance);
        }
        std::cout << std::endl;
        ++it;
        ++idx;
    }
}

template<typename EngineType>
void TestCase_GivenHighRepeatAndLowTolerance_ExpectSuccess()
{
    std::vector<int> randomNumbers{ -1, 0, 1, 2, 3, 4, 5 };
    std::vector<double> probabilities{ 0.01, 0.3, 0.58 - 2E-5, 0.1, 0.01, 1E-5, 1E-5 };
    DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);

    std::map<int, size_t> frequencyMap;
    for (auto x : randomNumbers) {
        // initialize as zero, in case that no such number is generated
        frequencyMap[x] = 0;
    }

    auto repeat = 4000000;
    for (auto i = 0; i < repeat; ++i) {
        auto rdn = myDRNG.nextNum();
        ++frequencyMap[rdn];
    }

    const double relativeTolerance = 0.05;
    const double probThreshold = 1e-5;
    const double absoluteTolerance = probThreshold;

    auto it = frequencyMap.begin();
    auto idx = 0;
    double repeatDouble = repeat;
    for (auto prob : probabilities) {
        std::cout << "Random num: " << it->first
            << ", Frequency: " << it->second
            << ", probability expected: " << prob
            << ", probability actual: " << it->second / repeatDouble;
        assert(it->first == randomNumbers[idx]);
        if (prob > probThreshold) {
            std::cout << ", rel diff: " << fabs(prob - it->second / repeatDouble) / prob;
            assert(fabs(prob - it->second / repeatDouble) / prob <= relativeTolerance);
        }
        else {
            std::cout << ", abs diff: " << fabs(prob - it->second / repeatDouble);
            assert(fabs(prob - it->second / repeatDouble) <= absoluteTolerance);
        }

        std::cout << std::endl;
        ++it;
        ++idx;
    }
}

template<typename EngineType>
void TestCase_GivenInvalidParameters_ExpectFailure()
{
    std::string testString;
    try {
        std::vector<int> randomNumbers;
        std::vector<double> probabilities;
        DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);
    }
    catch (CreationException& e) {
        testString = e.what();
    }
    catch (...){
    }
    assert(testString ==
        "DiscreteRandomNumberGenerator: Fail to construct - randomNumbers.empty()");

    try{
        std::vector<int> randomNumbers{ 1 };
        std::vector<double> probabilities;
        DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);
    }
    catch (CreationException& e) {
        testString = e.what();
    }
    catch (...) {
    }
    assert(testString ==
        "DiscreteRandomNumberGenerator: Fail to construct - probabilities.empty()");

    try {
        std::vector<int> randomNumbers{ -1, 0, 1, 2, 3 };
        std::vector<double> probabilities{ 0.01, 0.3, 0.58, 0.1 };
        DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);
    }
    catch (CreationException& e) {
        testString = e.what();
    }
    catch (...) {
    }

    assert(testString ==
        "DiscreteRandomNumberGenerator: Fail to construct - randomNumbers.size() != probabilites.size()");

    try {
        std::vector<int> randomNumbers{ -1, 0, 1, 2, 3 };
        std::vector<double> probabilities{ 0.01, 0.3, -0.58, 0.1, 0.01 };
        DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);
    }
    catch (CreationException& e) {
        testString = e.what();
    }
    catch (...) {
    }

    assert(testString ==
        "DiscreteRandomNumberGenerator: Fail to construct - negative value in probabilities");

    try {
        std::vector<int> randomNumbers{ -1, 0, 1, 2, 3 };
        std::vector<double> probabilities{ 0.0, 0.0, 0.0, 0.0, 0.0 };
        DiscreteRandomNumberGenerator<EngineType, int> myDRNG(randomNumbers, probabilities);
    }
    catch (CreationException& e) {
        testString = e.what();
    }
    catch (...) {
    }

    assert(testString ==
        "DiscreteRandomNumberGenerator: Fail to construct - no positive value in probabilities");
}
}// namespace MyRandom

int main(int argc, char* argv[])
{
    MyRandom::TestCase_GivenInvalidParameters_ExpectFailure<std::mt19937>();
    MyRandom::TestCase_GivenInvalidParameters_ExpectFailure<std::minstd_rand0>();
    MyRandom::TestCase_GivenInvalidParameters_ExpectFailure<std::knuth_b>();
    MyRandom::TestCase_GivenLowRepeatAndHighTolerance_ExpectSuccess<std::mt19937>();
    MyRandom::TestCase_GivenHighRepeatAndLowTolerance_ExpectSuccess<std::mt19937>();
    MyRandom::TestCase_GivenLowRepeatAndHighTolerance_ExpectSuccess<std::minstd_rand0>();
    MyRandom::TestCase_GivenHighRepeatAndLowTolerance_ExpectSuccess<std::minstd_rand0>();
    MyRandom::TestCase_GivenLowRepeatAndHighTolerance_ExpectSuccess<std::knuth_b>();
    MyRandom::TestCase_GivenHighRepeatAndLowTolerance_ExpectSuccess<std::knuth_b>();

    return 0;
}

/*
Output -

TEST[]$ ./DiscreteRandomNumberGenerator
Random num: -1, Frequency: 988, probability expected: 0.01, probability actual: 0.00988, rel diff: 0.012
Random num: 0, Frequency: 29857, probability expected: 0.3, probability actual: 0.29857, rel diff: 0.00476667
Random num: 1, Frequency: 58024, probability expected: 0.57998, probability actual: 0.58024, rel diff: 0.000448291
Random num: 2, Frequency: 10221, probability expected: 0.1, probability actual: 0.10221, rel diff: 0.0221
Random num: 3, Frequency: 909, probability expected: 0.01, probability actual: 0.00909, rel diff: 0.091
Random num: 4, Frequency: 1, probability expected: 1e-05, probability actual: 1e-05, abs diff: 0
Random num: 5, Frequency: 0, probability expected: 1e-05, probability actual: 0, abs diff: 1e-05
Random num: -1, Frequency: 40142, probability expected: 0.01, probability actual: 0.0100355, rel diff: 0.00355
Random num: 0, Frequency: 1198930, probability expected: 0.3, probability actual: 0.299733, rel diff: 0.000891667
Random num: 1, Frequency: 2321344, probability expected: 0.57998, probability actual: 0.580336, rel diff: 0.000613814
Random num: 2, Frequency: 399953, probability expected: 0.1, probability actual: 0.0999883, rel diff: 0.0001175
Random num: 3, Frequency: 39518, probability expected: 0.01, probability actual: 0.0098795, rel diff: 0.01205
Random num: 4, Frequency: 59, probability expected: 1e-05, probability actual: 1.475e-05, abs diff: 4.75e-06
Random num: 5, Frequency: 54, probability expected: 1e-05, probability actual: 1.35e-05, abs diff: 3.5e-06
Random num: -1, Frequency: 992, probability expected: 0.01, probability actual: 0.00992, rel diff: 0.008
Random num: 0, Frequency: 29786, probability expected: 0.3, probability actual: 0.29786, rel diff: 0.00713333
Random num: 1, Frequency: 58223, probability expected: 0.57998, probability actual: 0.58223, rel diff: 0.00387944
Random num: 2, Frequency: 10005, probability expected: 0.1, probability actual: 0.10005, rel diff: 0.0005
Random num: 3, Frequency: 993, probability expected: 0.01, probability actual: 0.00993, rel diff: 0.007
Random num: 4, Frequency: 1, probability expected: 1e-05, probability actual: 1e-05, abs diff: 0
Random num: 5, Frequency: 0, probability expected: 1e-05, probability actual: 0, abs diff: 1e-05
Random num: -1, Frequency: 39895, probability expected: 0.01, probability actual: 0.00997375, rel diff: 0.002625
Random num: 0, Frequency: 1200122, probability expected: 0.3, probability actual: 0.30003, rel diff: 0.000101667
Random num: 1, Frequency: 2320647, probability expected: 0.57998, probability actual: 0.580162, rel diff: 0.000313373
Random num: 2, Frequency: 399276, probability expected: 0.1, probability actual: 0.099819, rel diff: 0.00181
Random num: 3, Frequency: 39990, probability expected: 0.01, probability actual: 0.0099975, rel diff: 0.00025
Random num: 4, Frequency: 36, probability expected: 1e-05, probability actual: 9e-06, abs diff: 1e-06
Random num: 5, Frequency: 34, probability expected: 1e-05, probability actual: 8.5e-06, abs diff: 1.5e-06
Random num: -1, Frequency: 966, probability expected: 0.01, probability actual: 0.00966, rel diff: 0.034
Random num: 0, Frequency: 30136, probability expected: 0.3, probability actual: 0.30136, rel diff: 0.00453333
Random num: 1, Frequency: 58024, probability expected: 0.57998, probability actual: 0.58024, rel diff: 0.000448291
Random num: 2, Frequency: 9911, probability expected: 0.1, probability actual: 0.09911, rel diff: 0.0089
Random num: 3, Frequency: 962, probability expected: 0.01, probability actual: 0.00962, rel diff: 0.038
Random num: 4, Frequency: 1, probability expected: 1e-05, probability actual: 1e-05, abs diff: 0
Random num: 5, Frequency: 0, probability expected: 1e-05, probability actual: 0, abs diff: 1e-05
Random num: -1, Frequency: 39920, probability expected: 0.01, probability actual: 0.00998, rel diff: 0.002
Random num: 0, Frequency: 1199834, probability expected: 0.3, probability actual: 0.299959, rel diff: 0.000138333
Random num: 1, Frequency: 2320135, probability expected: 0.57998, probability actual: 0.580034, rel diff: 9.26756e-05
Random num: 2, Frequency: 400077, probability expected: 0.1, probability actual: 0.100019, rel diff: 0.0001925
Random num: 3, Frequency: 39953, probability expected: 0.01, probability actual: 0.00998825, rel diff: 0.001175
Random num: 4, Frequency: 46, probability expected: 1e-05, probability actual: 1.15e-05, abs diff: 1.5e-06
Random num: 5, Frequency: 35, probability expected: 1e-05, probability actual: 8.75e-06, abs diff: 1.25e-06
*/
