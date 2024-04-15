/*
@copyright Copyright 2024 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.
*/

#include "UtLambertW.hh"
#include "software/exceptions/TsOutOfBoundsException.hh"
#include <vector>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] input       (--) Test input value.
/// @param[in] expected    (--) Expected test result.
/// @param[in] convergence (--) Test convergence value and tolerance.
///
/// @details  Default constructs this Lambert W Function Unit Test Input Set.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertWInputSet::UtLambertWInputSet(const double input, const double expected, const double convergence)
    :
    mInput(input),
    mExpected(expected),
    mConvergence(convergence)
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs this Lambert W Function Unit Test Input Set.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertWInputSet::~UtLambertWInputSet()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] that (--) Reference to the object to be copied.
///
/// @details  Copy constructs this Lambert W Function Unit Test Input Set by reusing the assignment
///           operator.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertWInputSet::UtLambertWInputSet(const UtLambertWInputSet& that)
{
    *this = that;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] that (--) Reference to the object to be assigned equal to.
///
/// @returns  UtLambertWInputSet& (--) Reference to this object.
///
/// @details  Assigns this Lambert W Function Unit Test Input Set equal to the given set.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertWInputSet& UtLambertWInputSet::operator =(const UtLambertWInputSet& that)
{
    if (this != &that) {
        this->mInput = that.mInput;
        this->mExpected = that.mExpected;
        this->mConvergence = that.mConvergence;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default constructs this Lambert W Function unit test.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertW::UtLambertW()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs this Lambert W Function unit test.
////////////////////////////////////////////////////////////////////////////////////////////////////
UtLambertW::~UtLambertW()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Executed before each unit test as part of the CPPUNIT framework.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::setUp()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Executed after each unit test as part of the CPPUNIT framework.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::tearDown()
{
    //do nothing
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Verifies the solveW0 function will return the correct solution of the Lambert W
///           principal branch.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::testW0Nominal()
{
    std::cout << "\n -----------------------------------------------------------------------------";
    std::cout << "\n UtLambertW ...... 01: testW0Nominal ................................";

    /// - Create a set of test conditions to test all the normal and special regions of the
    ///   solution method.
    std::vector<UtLambertWInputSet> inputSets;
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0),           -1.0,               0.0));
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0) + 1.0e-10, -0.999976683739455, 1.0e-14));
    inputSets.push_back(UtLambertWInputSet(-0.2,                         -0.259171101819074, 1.0e-14));
    inputSets.push_back(UtLambertWInputSet(-1.0e-20,                     -1.0e-20,           0.0 ));
    inputSets.push_back(UtLambertWInputSet( 0.0,                          0.0,               0.0 ));
    inputSets.push_back(UtLambertWInputSet( 1.0e-20,                      1.0e-20,           0.0 ));
    inputSets.push_back(UtLambertWInputSet( 0.2,                          0.16891597349911,  1.0e-14));
    inputSets.push_back(UtLambertWInputSet( std::exp(1.0) - 1.0e-10,      0.999999999981606, 1.0e-14));
    inputSets.push_back(UtLambertWInputSet( std::exp(1.0),                1.0,               0.0));
    inputSets.push_back(UtLambertWInputSet( std::exp(1.0) + 1.0e-10,      1.00000000001839,  1.0e-14));
    inputSets.push_back(UtLambertWInputSet( 100.0,                        3.38563014029005,  1.0e-6));
    inputSets.push_back(UtLambertWInputSet( 1.0e300,                      684.247208629761,  1.0e-12));

    for(unsigned int i=0; i<inputSets.size(); ++i) {
        const double result = LambertW::solveW0(inputSets[i].mInput, inputSets[i].mConvergence);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(inputSets[i].mExpected, result, inputSets[i].mConvergence);
    }

    std::cout << "... Pass";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Verifies the response of the solveW0 function given invalid inputs.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::testW0Errors()
{
    std::cout << "\n UtLambertW ...... 02: testW0Errors .................................";

    /// - Create a set of test conditions to test all the out of bounds checks.
    std::vector<UtLambertWInputSet> inputSets;
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0) - 1.0e-10, 0.0, 0.0));
    inputSets.push_back(UtLambertWInputSet(1.01e300,                     0.0, 0.0));

    for(unsigned int i=0; i<inputSets.size(); ++i) {
        CPPUNIT_ASSERT_THROW(LambertW::solveW0(inputSets[i].mInput, inputSets[i].mConvergence), TsOutOfBoundsException);
    }

    std::cout << "... Pass";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Verifies the solveW1 function will return the correct solution of the Lambert W
///           non-principal branch.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::testW1Nominal()
{
    std::cout << "\n UtLambertW ...... 03: testW1Nominal ................................";

    /// - Create a set of test conditions to test all the normal and special regions of the
    ///   solution method.
    std::vector<UtLambertWInputSet> inputSets;
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0),           -1.0,              0.0));
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0) + 1.0e-10, -1.00002331662264, 1.0e-13));
    inputSets.push_back(UtLambertWInputSet(-0.3,                         -1.78133702342163, 1.0e-13));
    inputSets.push_back(UtLambertWInputSet(-0.008 - 1.0e-10,             -6.73574164692848, 1.0e-13 ));
    inputSets.push_back(UtLambertWInputSet(-0.008,                       -6.73574166160779, 1.0e-13 ));
    inputSets.push_back(UtLambertWInputSet(-0.008 + 1.0e-10,             -6.73574167628711, 1.0e-13 ));
    inputSets.push_back(UtLambertWInputSet(-1.0e-5,                      -14.1636008158102, 1.0e-12));
    inputSets.push_back(UtLambertWInputSet(-1.0e-300,                    -697.32277629546,  1.0e-11));

    for(unsigned int i=0; i<inputSets.size(); ++i) {
        const double result = LambertW::solveW1(inputSets[i].mInput, inputSets[i].mConvergence);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(inputSets[i].mExpected, result, inputSets[i].mConvergence);
    }

    std::cout << "... Pass";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Verifies the response of the solveW1 function given invalid inputs.
////////////////////////////////////////////////////////////////////////////////////////////////////
void UtLambertW::testW1Errors()
{
    std::cout << "\n UtLambertW ...... 04: testW1Errors .................................";

    /// - Create a set of test conditions to test all the out of bounds checks.
    std::vector<UtLambertWInputSet> inputSets;
    inputSets.push_back(UtLambertWInputSet(-1.0/std::exp(1.0) - 1.0e-10, 0.0, 0.0));
    inputSets.push_back(UtLambertWInputSet(0.0,                          0.0, 0.0));

    for(unsigned int i=0; i<inputSets.size(); ++i) {
        CPPUNIT_ASSERT_THROW(LambertW::solveW1(inputSets[i].mInput, inputSets[i].mConvergence), TsOutOfBoundsException);
    }

    std::cout << "... Pass";
}
