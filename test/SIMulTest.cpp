/** File @file is intended to be used as a Unit Test file to test the integretiy of the Mulitiplcation
operator for the System of Units Template Class.
*/

//#include <cppunit/extensions/HelperMacros.h>
#include <gtest/gtest.h>
//#include <gtest/internal/gtest-internal.h>
//#include <gtest/internal/gtest-param-util.h>
//#include <gtest/internal/gtest-param-util-generated.h>

#include "SI.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"	/// helps out during one of the test
#include "template_help.h"
#include <memory>
//namespace {

// basic test on the multiplication operator
class MultiplyFirst : public ::testing::Test //: public CppUnit::TestFixture
{
public:
	typedef Metric::AtomicUnit::Meter Meter;
	typedef SOU::Time::AtomicUnit::second second;
	typedef Metric::AtomicUnit::gram gram;
	//typedef SOU::MakeType< Meter, second, gram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
	//typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
	//typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
	//typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;
	typedef Metric::t_meter t_Meter;

	//typedef 
	typedef Metric::AUMetric::MakeDim<2, 0, 0, 0, 0>::type t_MeterSq;
	typedef Metric::AUMetric::MakeDim<3, 0, 0, 0, 0>::type t_MeterCubed;

	typedef Metric::t_centimeter t_centimeter;
public:
	void SetUp() {}
	void TearDown() {}
private:
};
   ///Tests whether the dimensions are correct.
   /// STATIC_ASSERTION_FAILURE will bust out during compile time.
   TEST_F(MultiplyFirst, TestAssignment )
   {
      using namespace SOU::operators;

      EXPECT_TRUE( t_MeterSq::eL == 2 );
	  EXPECT_TRUE( t_MeterSq::et==0);
	  EXPECT_TRUE( t_MeterSq::eM==0);
	  EXPECT_TRUE( t_MeterSq::eT==0);
	  EXPECT_TRUE( t_MeterSq::eQ==0);

      typedef Mul_Result<t_Meter, t_Meter> tMulSq;
	  EXPECT_TRUE( tMulSq::ALLTYPES_THE_SAME::val == tMulSq::ALLTYPES_THE_SAME::T );
	  EXPECT_TRUE( tMulSq::TResult::eL==t_MeterSq::eL );//good
	  EXPECT_TRUE( tMulSq::TResult::et==t_MeterSq::et );
	  EXPECT_TRUE( tMulSq::TResult::eM==t_MeterSq::eM );
	  EXPECT_TRUE( tMulSq::TResult::eT==t_MeterSq::eT );
	  EXPECT_TRUE( tMulSq::TResult::eQ==t_MeterSq::eQ );
      //STATIC_ASSERTION_FAILURE(( boost::is_same<tMulSq::TResult::Length, SI::NoDim>::value ));

      tMulSq mulSq( t_Meter(1.0) , t_Meter(1.0) );
      //STATIC_ASSERTION_FAILURE(( boost::is_same< t_MeterSq, tMulSq::TResult >::value ));
      
      tMulSq::TResult sq = mulSq.result();
      t_MeterSq sq1 = mulSq.result();
   }
   /// test the class Mul_Result and see how it works.
   /// @see SystemOfUnits::operators::Mul_Result<T1,T2>
   TEST_F(MultiplyFirst, TestMul_Result )
   {
      using namespace SOU::operators;

	  // test basic 1x1 and if the dim is correct
      t_MeterSq sq( t_Meter(1.0) * t_Meter(1.0));
      EXPECT_TRUE( sq == 1.0 );
      
      t_MeterSq sq2 = t_Meter(1.0) * t_Meter(2.0);
	  EXPECT_TRUE( sq2 == 2.0 );
	  EXPECT_TRUE( 2.0 == sq2 ) << "not implemented yet";

      t_MeterSq sq3 = t_Meter(4.5) * t_Meter(5.5);
      EXPECT_DOUBLE_EQ(24.75, sq3.amount() );
   }
 
   /// test with a cube dimension.  Important test when first beginning
   TEST_F(MultiplyFirst, TestWithCube )
   {
      t_MeterCubed cu1 = t_Meter(2.0) * t_MeterSq(3.0);
      EXPECT_TRUE( cu1 == 6.0 );
      
      t_MeterCubed cu2 = t_MeterSq( 4.0 ) * t_Meter( 2.0 );
      EXPECT_TRUE( cu2 == 8.0 );
   }

   /** Test chainging of operator* and see if the result type will be correct
   The following test failed for good reasons since the result type did not match left-hand
   side of the assignment operator.
   @code t_MeterCubed const cu1 = t_Meter(2.0) * t_Meter(2.0); @endcode

   Test being able to use the following code:
   @code t_MeterCubed const cu1 = t_Meter(2.0) * t_Meter(2.0) * t_Meter(2.0); @endcode

   Test that the following will fail during compile time from the assignment to a const.
   @code 
   t_MeterCubed const cube = 26.0;
   cube = t_Meter(2.0) * t_Meter(2.0)* t_Meter(2.0);
   @endcod
   */
   TEST_F(MultiplyFirst, TestChaining )
   {
      t_MeterCubed const cu1 = t_Meter(2.0) * t_Meter(2.0) * t_Meter(2.0);
      EXPECT_TRUE( cu1 == 8.0 );

      t_Meter const x(2.0);
	   t_MeterCubed cu2 = x * t_Meter(2.0) * t_Meter(2.0);
      EXPECT_TRUE( cu2 == 8.0 );
      
	   t_Meter const y = 2.0;
	   t_MeterCubed cu3 = t_Meter(2.0) * y * t_Meter(2.0);
      EXPECT_TRUE( cu3 == 8.0 );

	   // test bad match this will be commented out after proving failure
      //cu1 = t_Meter(2.0) * t_Meter(2.0);
   }
  
   // What is this doing?  Does it really test whether the types are the same.
   TEST_F(MultiplyFirst, TestALLTYPES_THE_SAME )
   {
      using namespace SOU;
      using namespace SOU::operators;
      //typedef Mul_Result<t_Meter, t_Meter> tMulSq;
      //CPPUNIT_ASSERT( tMulSq::eALLTYPES_THE_SAME == true );
      EXPECT_TRUE( static_cast<bool>(Mul_Result<t_Meter, t_Meter>::ALLTYPES_THE_SAME::val ) == true );
	  EXPECT_TRUE(static_cast<bool>(Mul_Result<t_Meter, t_MeterSq>::ALLTYPES_THE_SAME::val) == true );
	  EXPECT_TRUE( static_cast<bool>(Mul_Result<t_MeterCubed, t_Meter>::ALLTYPES_THE_SAME::val) == true );

	  EXPECT_TRUE(static_cast<bool>(Mul_Result<t_centimeter, t_Meter>::ALLTYPES_THE_SAME::val) == true );
	  EXPECT_TRUE(static_cast<bool>(Mul_Result<t_centimeter, t_MeterCubed>::ALLTYPES_THE_SAME::val) == true );

	  EXPECT_TRUE(static_cast<bool>(Mul_Result<t_Meter, tNoUnit>::ALLTYPES_THE_SAME::val) == true );
	  EXPECT_TRUE(static_cast<bool>(Mul_Result<t_Meter, Metric::t_gramPsec>::ALLTYPES_THE_SAME::val) == true );
      // not implemented yet!!
   }
   ///Basic test with Length types
   TEST_F(MultiplyFirst, TestWithNonAtomicUnitUnitsLength )
   {
	   using t_Mul = SOU::operators::Mul_Result<t_Meter, Metric::t_centimeter > ;
	   EXPECT_TRUE( t_Mul::IsLengthSame == false );
	   EXPECT_TRUE( t_Mul::IsTimeSame == true );
	   EXPECT_TRUE( t_Mul::IsMassSame == true );
	   EXPECT_TRUE( t_Mul::AreLengthsBase == false );

	   using t_MulR = t_Mul::TResult ;
	   enum{ b = SOU::is_same< t_MulR::Length, Metric::AtomicUnit::Centimeter >::value };
	   enum{ c = SOU::is_same< t_MulR::Length, Metric::AtomicUnit::Meter >::value };
	   EXPECT_TRUE( c );
	   EXPECT_FALSE( b) << "this is correct Length should not be a Centimeter";

      t_Mul mul( t_Meter(7.0), Metric::t_centimeter(200.0) );
      //CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, mul.result().amount(), 0.0001 );
      t_MeterSq meterSq2 = mul.result();
      //CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, meterSq2.amount(), 0.0001 );

	   const Metric::t_centimeter cent(200.0);
      EXPECT_DOUBLE_EQ( 200.0, cent.amount() );
	  EXPECT_DOUBLE_EQ( 2.0, SOU::conversion_cast<t_Meter>( cent ).amount() );

	   const t_Meter meter = 7.0;
	   EXPECT_DOUBLE_EQ( 7.0, meter.amount() );
	   EXPECT_DOUBLE_EQ( 700.0, SOU::conversion_cast<Metric::t_centimeter>(meter).amount() );

	   t_MeterSq meterSq;
	   meterSq = meter * cent; 
	   // 
	   EXPECT_DOUBLE_EQ( 14.0, meterSq.amount() ) << "this test caused problems since kilogram is the base mass. fixed problem in operator.h";

	   typedef SOU::MakeSQ<Metric::t_centimeter>::type t_cmSQ;
	   t_cmSQ cmSQ = cent * meter;
	   EXPECT_DOUBLE_EQ( 140000.0, cmSQ.amount() );

	   Metric::t_kilometer k = 4.0;
	   t_Meter m = 4000.0; //k * 1.0;

	   t_MeterSq m2 = m * k; //k * m;
	   EXPECT_DOUBLE_EQ( 16000000.0, m2.amount() );

	   typedef SOU::MakeSQ<Metric::t_kilometer>::type t_kmSQ;
	   t_kmSQ kmSQ = k * m;
	   EXPECT_DOUBLE_EQ( 16.0, kmSQ.amount() );

	   kmSQ = k * Metric::t_centimeter( 100000.0 );
	   EXPECT_DOUBLE_EQ( 4.0, kmSQ.amount() );

	   typedef SOU::MakeSQ<Metric::t_milimeter>::type t_mmSQ;
	   m = 4.0;
	   t_mmSQ mmSq = Metric::t_milimeter( 5.0 ) * m;
	   EXPECT_DOUBLE_EQ( 20000.0, mmSq.amount() );

	   t_MeterSq m3 = m * Metric::t_milimeter( 5.0 );
	   EXPECT_DOUBLE_EQ( 0.02, m3.amount() );
   }
   /// Basic test with time units
   TEST_F(MultiplyFirst, TestWithNonAtomicUnitUnitsTime )
   {
      typedef SOU::MakeSQ<Metric::t_second>::type t_sSQ;
      typedef SOU::MakeSQ<Metric::t_minute>::type t_mSQ;
      typedef SOU::MakeSQ<Metric::t_hour>::type t_hrSQ;

      t_sSQ const s1 = Metric::t_second(3) * Metric::t_second(4);
	  EXPECT_DOUBLE_EQ( 12.0, s1.amount() );
      
      t_sSQ const s2 = Metric::t_second( 3.0 ) * Metric::t_minute( 1.0 );
	  EXPECT_DOUBLE_EQ( 180.0, s2.amount() );

      t_mSQ const m1 = Metric::t_minute( 2.0 ) * Metric::t_second( 120.0 );
	  EXPECT_DOUBLE_EQ( 4.0, m1.amount() );

      t_mSQ const m2 = Metric::t_minute( 2.0 ) * Metric::t_hour(1.0);
	  EXPECT_DOUBLE_EQ( 120.0, m2.amount() );

      t_hrSQ const hr1 = Metric::t_hour( 1.0 ) * Metric::t_second( 7200 );
	  EXPECT_DOUBLE_EQ( 2.0, hr1.amount() );

   }
   ///Basic test with mass types
   TEST_F(MultiplyFirst, TestWithNonAtomicUnitUnitsMass )
   {
      using namespace Metric;
      namespace AU = AtomicUnit;
      typedef SOU::unitType< AU::Meter, 0, SOU::Time::AtomicUnit::second, -1, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_Hertz;
      
      Metric::t_gram const g = 25.0;
      t_Hertz h = 3.0;

      Metric::t_gramPsec gps = g * h;
	  EXPECT_DOUBLE_EQ( 75.0, gps.amount() );
   }
   /// Test with the non-dimensional unit type to ensure that operator* still works with
   /// type of 0 dimension.
   TEST_F(MultiplyFirst, TestWithNonDimension )
   {
      const t_Meter meter = 7.0;
      double y = 2.0;
	  EXPECT_TRUE(14.00 == meter * 2) << "with a scalar value";
	  EXPECT_TRUE(14.00 == 2 * meter ) << "with a scalar value";
      t_Meter high = meter * y;
      EXPECT_TRUE(high == 14.0 ) << "testing with variable" ;
	  EXPECT_TRUE( 21.0 == meter * 3.0 ) << "testing unitType*constant";
	  EXPECT_TRUE(3.0 * meter == 21.0 ) << "testing constant * unitType";

      double const x = 4;
      //t_Meter low = meter * tNoUnit(3.0);
      //low = meter * x;
	  EXPECT_TRUE( meter * x == 28.0 ) << "testing with constant variable" ;
	  EXPECT_TRUE( meter * 5 == 35.0 ) << "test with a int";

	  EXPECT_TRUE( meter * static_cast<float>(5.0) == 35.0 ) << "test with a float";
	  EXPECT_TRUE( 12.0 == x * 3 ) << "is this still allowed";

	  EXPECT_TRUE( 0 == meter * 0.0 ) << "with zero";
	  EXPECT_TRUE( 0 == 0 * meter );
	  //EXPECT_DOUBLE_EQ( t_Meter(0.0), 0.0 * meter) << "find out why it will not compile.";
	  EXPECT_TRUE( t_Meter(0) == meter * 0.0 );
	  EXPECT_TRUE(0.0 == meter * 0.0);

      Metric::t_kilometer km = 3.0 * Metric::t_kilometer(1.0);
	  EXPECT_DOUBLE_EQ( 3.0, km.amount() );
      km = Metric::t_kilometer(1.0) * 3;
	  EXPECT_DOUBLE_EQ( 3.0, km.amount() );
      EXPECT_TRUE( Metric::t_kilometer(3.0) == 3.0 * Metric::t_kilometer(1.0) );
   }

   /// Test with a multiplication after an subtraction
   TEST_F(MultiplyFirst, TestWithSubinside )
   {
      typedef Metric::t_second second;
      second Tmin = 55.5;
      second Tmax = 105.5;
      second Topt = Tmin + 0.7 * ( Tmax - Tmin );
      EXPECT_DOUBLE_EQ( 90.5, Topt.amount() );
   }

//   /// MultiplyFirst suite
//  CPPUNIT_TEST_SUITE( MultiplyFirst );
//  CPPUNIT_TEST( TestAssignment );
//  CPPUNIT_TEST( TestMul_Result );
//  CPPUNIT_TEST( TestWithCube );
//  CPPUNIT_TEST( TestChaining );
//  CPPUNIT_TEST( TestALLTYPES_THE_SAME );
//  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsLength );
//  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsTime );
//  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsMass );
//  CPPUNIT_TEST( TestWithNonDimension );
//  CPPUNIT_TEST( TestWithSubinside );
//  CPPUNIT_TEST_SUITE_END();
//};
//
//CPPUNIT_TEST_SUITE_REGISTRATION( MultiplyFirst );
template< int NUM_X, int NUM_Y, int PROD > struct ARG{ enum { eX = NUM_X, eY = NUM_Y, ePROD = PROD }; };

///class template to test multiplication operator against any different type of different
///dimensions in their quantity
//template
//< int PROD /// The product of the two arguments
//, int MUL1 /// Argument type 1
//, int MUL2 /// Argument type 2
//>
template< typename T_ARG >
class SI_Multiply : public testing::Test //: public CppUnit::TestFixture
{
public:
	enum { MUL1 = T_ARG::eX, MUL2 = T_ARG::eY, PROD = T_ARG::ePROD };

	//using namespace Metric;
	typedef Metric::AtomicUnit::Meter Meter;
	typedef SOU::Time::AtomicUnit::second second;
	typedef Metric::AtomicUnit::gram gram;
	typedef Metric::AtomicUnit::coulomb coul;
	typedef Metric::AtomicUnit::kelvin kelvin;
	///argument 1 for operator testing
	typedef SOU::unitType< Meter, MUL1, second, 0, gram, 0, kelvin, 0, coul, 0 > t_1;
	///argument 2 for operator testing
	typedef SOU::unitType< Meter, MUL2, second, 0, gram, 0, kelvin, 0, coul, 0 > t_2;
	/// product type for the result of operator* testing
	typedef SOU::unitType< Meter, PROD, second, 0, gram, 0, kelvin, 0, coul, 0 > t_3;

	SI_Multiply() : m_delta(0.0000001) {}

	void SetUp()
	{
		m_1 = std::make_unique<t_1>(3.0);
		m_2 = std::make_unique<t_2>(4.0);
		m_3 = std::make_unique<t_3>(12.0);
	}
	void TearDown()
	{
		//delete m_1;
		//delete m_2;
		//delete m_3;
	}
protected:
	std::unique_ptr<t_1> m_1; /// Argument one
	std::unique_ptr<t_2> m_2;  /// Argument two
	std::unique_ptr<t_3> m_3; /// The product of the two arguments

private:
	double const m_delta;

};

//typedef SI_Multiply<2, 1, 1> t_myMul;
//typedef testing::Types<2, 1, 1> t_arg;
//typedef testing::Types<int, int, int> t_arg;
TYPED_TEST_CASE_P(SI_Multiply);
//CPPUNIT_TEST_SUITE_REGISTRATION( t_myMul );

TYPED_TEST_P(SI_Multiply, NoTestHere)
{
	EXPECT_TRUE(true) << "Just set up to see if it would compile.";
}


   /// Test the result type and shows that the result type is working correctly.
TYPED_TEST_P(SI_Multiply, TestMul_Result )
   {
      using namespace SOU::operators;
	  using TAG = SI_Multiply<TypeParam >;
      Mul_Result<TAG::t_1, TAG::t_2> sq_m( *TAG::m_1, *TAG::m_2 );
      EXPECT_TRUE( sq_m.result() == *TAG::m_3 ) << "testing the expression template for mult";

      Mul_Result<TAG::t_1, TAG::t_2> const sq_m2( *TAG::m_1, *TAG::m_2 );
	  EXPECT_TRUE(sq_m2.result() == *TAG::m_3 ) << "testing the expression template for mult";
   }

   /// First test with operator*() and shows that it is working correctly
	TYPED_TEST_P(SI_Multiply, Test2 )
   {
		using TAG = SI_Multiply<TypeParam >;
		// these test call internally Mul_Result
		TAG::t_3 prod = *TAG::m_1 * *TAG::m_2;
	  EXPECT_TRUE( prod == *TAG::m_3 );
	  EXPECT_TRUE( *TAG::m_3 == *TAG::m_1 * *TAG::m_2 );

      *TAG::m_3 = *TAG::m_1 * *TAG::m_2;
	  EXPECT_TRUE( *TAG::m_3 == 12.0 );

	  EXPECT_TRUE( *TAG::m_1 * *TAG::m_3 == *TAG::m_1 * *TAG::m_1 * *TAG::m_2 ) << "some chaining" ;
	  EXPECT_TRUE( *TAG::m_1 * *TAG::m_3 * *TAG::m_2 == *TAG::m_1 * *TAG::m_1 * *TAG::m_2 * *TAG::m_2 ) << "some chaining";
	  EXPECT_TRUE((*TAG::m_1 * *TAG::m_3) * *TAG::m_2 == *TAG::m_1 * (*TAG::m_1 * *TAG::m_2) * *TAG::m_2 ) << "some chaining";
	  EXPECT_TRUE( *TAG::m_1 * (*TAG::m_3 * *TAG::m_2) == (*TAG::m_1 * *TAG::m_1) * (*TAG::m_2 * *TAG::m_2) ) << "some chaining";

   }
   /// Test operator*() with scalar values.
	TYPED_TEST_P(SI_Multiply, TestWithScaler )
   {
		using TAG = SI_Multiply<TypeParam >;

		EXPECT_TRUE( 12.0 == *TAG::m_1 * 4.0 );
		EXPECT_TRUE(TAG::t_1(12.0) == *TAG::m_1 * 4.0 );
		EXPECT_TRUE(TAG::t_1(12.0) == 4.0 * *TAG::m_1 );

		EXPECT_TRUE( 16.0 == *TAG::m_2 * 4.0 );
		EXPECT_TRUE(TAG::t_2(16.0) == *TAG::m_2 * 4.0 );
		EXPECT_TRUE(TAG::t_2(16.0) == 4.0 * *TAG::m_2);

		EXPECT_TRUE( 48.0 == *TAG::m_3 * 4.0 );
		EXPECT_TRUE(TAG::t_3(48.0) == *TAG::m_3 * 4.0 );
		EXPECT_TRUE(TAG::t_3(48.0) == *TAG::m_3 * 2.0 * 2.0 ) << "with some chaining";
		EXPECT_TRUE(TAG::t_3(48.0) == 2.0 * *TAG::m_3 * 2.0 ) << "with some chaining";
		EXPECT_TRUE(TAG::t_3(48.0) == 2.0 * 2.0 * *TAG::m_3 ) << "with some chaining";

	  /// Test with integers
		EXPECT_TRUE( 12 == *TAG::m_1 * 4 );
		EXPECT_TRUE(TAG::t_1(12) == *TAG::m_1 * 4 );
		EXPECT_TRUE(TAG::t_1(12) == 4 * *TAG::m_1 );

		EXPECT_TRUE( 16.0 == *TAG::m_2 * 4 );
		EXPECT_TRUE(TAG::t_2(16.0) == *TAG::m_2 * 4 );
		EXPECT_TRUE(TAG::t_2(16.0) == 4 * *TAG::m_2);

		EXPECT_TRUE( 48.0 == *TAG::m_3 * 4 );
		EXPECT_TRUE(TAG::t_3(48.0) == *TAG::m_3 * 4 );
		EXPECT_TRUE(TAG::t_3(48.0) == *TAG::m_3 * 2 * 2.0 ) << "with some chaining";
		EXPECT_TRUE(TAG::t_3(48.0) == 2 * *TAG::m_3 * 2 ) << "with some chaining";
   }
   
	/// Have chaining with scalar values. Inside of a for-loop
	TYPED_TEST_P(SI_Multiply, TestChainWithScaler)
	{
		using TAG = SI_Multiply<TypeParam >;
		for (double x = 2.0; x < 12.0; x += 1.3)
		{
			TAG::t_3 arg1 = *TAG::m_3 *x*x;
			TAG::t_3 arg2 = (*TAG::m_1*x) *(*TAG::m_2 * x);
			EXPECT_DOUBLE_EQ(arg1.amount(), arg2.amount());
			//EXPECT_DOUBLE_EQ(*TAG::m_3 *x*x, (*TAG::m_1*x) *( *TAG::m_2 * x) ) << "Why didn't it work";
		}
	}

   /// test operator*=()
	TYPED_TEST_P(SI_Multiply, TestMultipleAssign )
   {
		using TAG = SI_Multiply<TypeParam >;
		*TAG::m_3 *= 2.0;
		EXPECT_DOUBLE_EQ( 24.0, TAG::m_3->amount() );

		*TAG::m_3 *= 0.5;
		EXPECT_DOUBLE_EQ( 12.0, TAG::m_3->amount() );

   }

   /** Test A_Trait<int,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<int,T2>
	*/
	TYPED_TEST_P(SI_Multiply, TestMultipleInt )
   {
		using TAG = SI_Multiply<TypeParam >;
		int const x = 2;
	   TAG::t_1 res1 = *TAG::m_1 * x;
	   TAG::t_1 const res2 = x * *TAG::m_1;

	   EXPECT_DOUBLE_EQ( 6.0, res1.amount() );
	   EXPECT_DOUBLE_EQ( 6.0, res2.amount() );
   }

   /** Test A_Trait<unsigned,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<unsigned,T2>

	When @code SystemOfUnits::operators::A_Trait<unsigned,T2> @endcode was commented out the below method failed to
	compile.
	*/ // @code meter z = 3.0 * y; @endcode
	TYPED_TEST_P(SI_Multiply, TestMultipleUnsigned )
   {
		using TAG = SI_Multiply<TypeParam >;
		unsigned const x = 2;
	   TAG::t_1 res1 = *TAG::m_1 * x;
	   TAG::t_1 const res2 = x * *TAG::m_1;

	   EXPECT_DOUBLE_EQ( 6.0, res1.amount() );
	   EXPECT_DOUBLE_EQ( 6.0, res2.amount() );
   }

   /** Test A_Trait<float,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<float,T2>
	*/
	TYPED_TEST_P(SI_Multiply, TestMultipleFloat )
   {
		using TAG = SI_Multiply<TypeParam >;
		float const x = 2.000f;
	   TAG::t_1 res1 = *TAG::m_1 * x;
	   TAG::t_1 const res2 = x * *TAG::m_1;

	   EXPECT_DOUBLE_EQ( 6.0, res1.amount() );
	   EXPECT_DOUBLE_EQ( 6.0, res2.amount());
   }

   /** Test A_Trait<short,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<short,T2>
	*/
	TYPED_TEST_P(SI_Multiply, TestMultipleShort )
   {
		using TAG = SI_Multiply<TypeParam >;
		short const x = 2;
	   TAG::t_1 res1 = *TAG::m_1 * x;
	   TAG::t_1 const res2 = x * *TAG::m_1;

	   EXPECT_DOUBLE_EQ( 6.0, res1.amount() );
	   EXPECT_DOUBLE_EQ( 6.0, res2.amount() );
   }

   /** Test A_Trait<short,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<short,T2>
	*/
	TYPED_TEST_P(SI_Multiply, TestMultipleLong )
   {
		using TAG = SI_Multiply<TypeParam >;
		long const x = 2;
	   auto res1 = *TAG::m_1 * x;
	   TAG::t_1 const res2 = x * *TAG::m_1;

	   EXPECT_DOUBLE_EQ( 6.0, res1.amount() );
	   EXPECT_DOUBLE_EQ( 6.0, res2.amount() );
   }

	REGISTER_TYPED_TEST_CASE_P(SI_Multiply
		, NoTestHere, TestMul_Result, Test2, TestWithScaler, TestMultipleAssign, TestChainWithScaler, TestMultipleInt, TestMultipleUnsigned, TestMultipleFloat, TestMultipleShort, TestMultipleLong);

//   CPPUNIT_TEST_SUITE( SI_Multiply );
//   CPPUNIT_TEST( TestMul_Result );
//   CPPUNIT_TEST( Test2 );
//   CPPUNIT_TEST( TestWithScaler );
//   CPPUNIT_TEST( TestMultipleAssign );
//   CPPUNIT_TEST( TestChainWithScaler );
//   CPPUNIT_TEST( TestMultipleInt );
//   CPPUNIT_TEST( TestMultipleUnsigned );
//   CPPUNIT_TEST( TestMultipleFloat );
//   CPPUNIT_TEST( TestMultipleShort );
//   CPPUNIT_TEST( TestMultipleLong );
//   CPPUNIT_TEST_SUITE_END();
//};
	typedef ::testing::Types< ARG<1, 1, 2>, ARG< 2, 0, 2>, ARG< 2, 1, 3>, ARG<2, 3, 5>, ARG<-3, 5, 2>, ARG<3, -5, -2> > MyTypes;
	INSTANTIATE_TYPED_TEST_CASE_P(My, SI_Multiply, MyTypes);
	using t_myArg = ARG<1,1,2>;
	//INSTANTIATE_TYPED_TEST_CASE_P(My, SI_Multiply, t_myArg );

//typedef SI_Multiply<2,1,1> t_myMul;
//TYPED_TEST_CASE(SI_Multiply, t_myMul);
////CPPUNIT_TEST_SUITE_REGISTRATION( t_myMul );
//
//typedef SI_Multiply<2,2,0> t_myMul1;
//CPPUNIT_TEST_SUITE_REGISTRATION( t_myMul1 );
//
//typedef SI_Multiply<3,2,1> t_Mul2;
//CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul2 );
//
//typedef SI_Multiply<5,2,3> t_Mul3;
//CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul3 );
//
//typedef SI_Multiply<2,-3,5> t_Mul4;
//CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul4 );
//
//typedef SI_Multiply<-2,3,-5> t_Mul5;
//CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul5 );
// }

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.
