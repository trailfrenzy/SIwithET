/** File @file is intended to be used as a Unit Test file to test the integretiy of the Mulitiplcation
operator for the System of Units Template Class.

*/

#include <cppunit/extensions/HelperMacros.h>
#include "SI.h"
#include "MetricTypes.h"
#include "operators.h"
#include "conversion_cast.h"	/// helps out during one of the test
//namespace {

// basic test on the multiplication operator
class MultiplyFirst : public CppUnit::TestFixture
{
   typedef Metric::AtomicUnit::Meter Meter;
   typedef SOU::Time::AtomicUnit::second second;
   typedef Metric::AtomicUnit::gram gram;
   //typedef SOU::MakeType< Meter, second, gram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
   //typedef SOU::MakeType< Meter, second, Metric::AtomicUnit::kilogram, Metric::AtomicUnit::kelvin, Metric::AtomicUnit::coulomb > t_Base;
   //typedef SI::unitType< Meter, 1, second, 0, gram, 0 > t_Meter;
   //typedef t_Base::MakeDim<1,0,0,0,0>::type t_Meter;
   typedef Metric::t_meter t_Meter;

   //typedef 
   typedef Metric::AUMetric::MakeDim<2,0,0,0,0>::type t_MeterSq;
   typedef Metric::AUMetric::MakeDim<3,0,0,0,0>::type t_MeterCubed;
   
   typedef Metric::t_centimeter t_centimeter;
public:
   void setUp()
   {
   }
   void tearDown()
   {
   }
private:

   ///Tests wheather the dimensions are correct.
   /// BOOST_STATIC_ASSERT will bust out during compile time.
   void TestAssignment()
   {
      using namespace SOU::operators;

      BOOST_STATIC_ASSERT( t_MeterSq::eL == 2 );
      BOOST_STATIC_ASSERT( t_MeterSq::et==0);
      BOOST_STATIC_ASSERT( t_MeterSq::eM==0);
      BOOST_STATIC_ASSERT( t_MeterSq::eT==0);
      BOOST_STATIC_ASSERT( t_MeterSq::eQ==0);

      typedef Mul_Result<t_Meter, t_Meter> tMulSq;
      CPPUNIT_ASSERT( tMulSq::eALLTYPES_THE_SAME == true );
      BOOST_STATIC_ASSERT( tMulSq::TResult::eL==t_MeterSq::eL );//good
      BOOST_STATIC_ASSERT( tMulSq::TResult::et==t_MeterSq::et );
      BOOST_STATIC_ASSERT( tMulSq::TResult::eM==t_MeterSq::eM );
      BOOST_STATIC_ASSERT( tMulSq::TResult::eT==t_MeterSq::eT );
      BOOST_STATIC_ASSERT( tMulSq::TResult::eQ==t_MeterSq::eQ );
      //BOOST_STATIC_ASSERT(( boost::is_same<tMulSq::TResult::Length, SI::NoDim>::value ));

      tMulSq mulSq( t_Meter(1.0) , t_Meter(1.0) );
      //BOOST_STATIC_ASSERT(( boost::is_same< t_MeterSq, tMulSq::TResult >::value ));
      
      tMulSq::TResult sq = mulSq.result();
      t_MeterSq sq1 = mulSq.result();
   }
   /// test the class Mul_Result and see how it works.
   /// @see SystemOfUnits::operators::Mul_Result<T1,T2>
   void TestMul_Result()
   {
      using namespace SOU::operators;

	  // test basic 1x1 and if the dim is correct
      t_MeterSq sq( t_Meter(1.0) * t_Meter(1.0));
      CPPUNIT_ASSERT( sq == 1.0 );
      
      t_MeterSq sq2 = t_Meter(1.0) * t_Meter(2.0);
      CPPUNIT_ASSERT( sq2 == 2.0 );
      CPPUNIT_ASSERT_MESSAGE("not implimented yet", 2.0 == sq2 );

      t_MeterSq sq3 = t_Meter(4.5) * t_Meter(5.5);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(24.75, sq3.amount(), 0.00001 );
   }

   /// test with a cube dimension.  Important test when first begining
   void TestWithCube()
   {
      t_MeterCubed cu1 = t_Meter(2.0) * t_MeterSq(3.0);
      CPPUNIT_ASSERT( cu1 == 6.0 );
      
      t_MeterCubed cu2 = t_MeterSq( 4.0 ) * t_Meter( 2.0 );
      CPPUNIT_ASSERT( cu2 == 8.0 );
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
   void TestChaining()
   {
      t_MeterCubed const cu1 = t_Meter(2.0) * t_Meter(2.0) * t_Meter(2.0);
      CPPUNIT_ASSERT( cu1 == 8.0 );

      t_Meter const x(2.0);
	   t_MeterCubed cu2 = x * t_Meter(2.0) * t_Meter(2.0);
      CPPUNIT_ASSERT( cu2 == 8.0 );
      
	   t_Meter const y = 2.0;
	   t_MeterCubed cu3 = t_Meter(2.0) * y * t_Meter(2.0);
      CPPUNIT_ASSERT( cu3 == 8.0 );

	   // test bad match this will be commented out after proving failure
      //cu1 = t_Meter(2.0) * t_Meter(2.0);
   }
  
   // What is this doing?  Does it really test whether the types are the same.
   void TestALLTYPES_THE_SAME()
   {
      using namespace SOU;
      using namespace SOU::operators;
      //typedef Mul_Result<t_Meter, t_Meter> tMulSq;
      //CPPUNIT_ASSERT( tMulSq::eALLTYPES_THE_SAME == true );
      CPPUNIT_ASSERT( (Mul_Result<t_Meter, t_Meter>::eALLTYPES_THE_SAME) == true );
      CPPUNIT_ASSERT( (Mul_Result<t_Meter, t_MeterSq>::eALLTYPES_THE_SAME) == true );
      CPPUNIT_ASSERT( (Mul_Result<t_MeterCubed, t_Meter>::eALLTYPES_THE_SAME) == true );

      CPPUNIT_ASSERT( (Mul_Result<t_centimeter, t_Meter>::eALLTYPES_THE_SAME) == true );
      CPPUNIT_ASSERT( (Mul_Result<t_centimeter, t_MeterCubed>::eALLTYPES_THE_SAME) == true );

      CPPUNIT_ASSERT( (Mul_Result<t_Meter, tNoUnit>::eALLTYPES_THE_SAME) == true );
      CPPUNIT_ASSERT( (Mul_Result<t_Meter, Metric::t_gramPsec>::eALLTYPES_THE_SAME) == true );
      // not implimeted yet!!
   }
   ///Basic test with Length types
   void TestWithNonAtomicUnitUnitsLength()
   {
	   typedef SOU::operators::Mul_Result<t_Meter, Metric::t_centimeter > t_Mul;
      BOOST_STATIC_ASSERT( t_Mul::IsLengthSame == false );
      BOOST_STATIC_ASSERT( t_Mul::IsTimeSame == true );
      BOOST_STATIC_ASSERT( t_Mul::IsMassSame == true );
      BOOST_STATIC_ASSERT( t_Mul::AreLengthsBase == false );

	   typedef t_Mul::TResult t_MulR;
	   enum{ b = boost::is_same< t_MulR::Length, Metric::AtomicUnit::Centimeter >::value };
	   enum{ c = boost::is_same< t_MulR::Length, Metric::AtomicUnit::Meter >::value };
	   BOOST_STATIC_ASSERT( c );
	   BOOST_STATIC_ASSERT( !b );  // this is correct Length should not be a Centimeter

      t_Mul mul( t_Meter(7.0), Metric::t_centimeter(200.0) );
      //CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, mul.result().amount(), 0.0001 );
      t_MeterSq meterSq2 = mul.result();
      //CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, meterSq2.amount(), 0.0001 );

	   const Metric::t_centimeter cent(200.0);
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 200.0, cent.amount(), 0.00001 );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 2.0, SOU::conversion_cast<t_Meter>( cent ).amount(), 0.00001 );

	   const t_Meter meter = 7.0;
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 7.0, meter.amount(), 0.00001 );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 700.0, SOU::conversion_cast<Metric::t_centimeter>(meter).amount(), 0.00001 );

	   t_MeterSq meterSq;
	   meterSq = meter * cent; 
	   // this test caused problems since kilogram is the base mass. fixed problem in operator.h
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 14.0, meterSq.amount(), 0.00001 );

	   typedef SOU::MakeSQ<Metric::t_centimeter>::type t_cmSQ;
	   t_cmSQ cmSQ = cent * meter;
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 140000.0, cmSQ.amount(), 0.000001 );

	   Metric::t_kilometer k = 4.0;
	   t_Meter m = 4000.0; //k * 1.0;

	   t_MeterSq m2 = m * k; //k * m;
	   CPPUNIT_ASSERT_EQUAL( 16000000.0, m2.amount() );

	   typedef SOU::MakeSQ<Metric::t_kilometer>::type t_kmSQ;
	   t_kmSQ kmSQ = k * m;
	   CPPUNIT_ASSERT_EQUAL( 16.0, kmSQ.amount() );

	   kmSQ = k * Metric::t_centimeter( 100000.0 );
	   CPPUNIT_ASSERT_EQUAL( 4.0, kmSQ.amount() );

	   typedef SOU::MakeSQ<Metric::t_milimeter>::type t_mmSQ;
	   m = 4.0;
	   t_mmSQ mmSq = Metric::t_milimeter( 5.0 ) * m;
	   CPPUNIT_ASSERT_EQUAL( 20000.0, mmSq.amount() );

	   t_MeterSq m3 = m * Metric::t_milimeter( 5.0 );
	   CPPUNIT_ASSERT_EQUAL( 0.02, m3.amount() );
   }
   /// Basic test with time units
   void TestWithNonAtomicUnitUnitsTime()
   {
      typedef SOU::MakeSQ<Metric::t_second>::type t_sSQ;
      typedef SOU::MakeSQ<Metric::t_minute>::type t_mSQ;
      typedef SOU::MakeSQ<Metric::t_hour>::type t_hrSQ;

      t_sSQ s1 = Metric::t_second(3) * Metric::t_second(4);
      CPPUNIT_ASSERT_EQUAL( 12.0, s1.amount() );
      
      t_sSQ s2 = Metric::t_second( 3.0 ) * Metric::t_minute( 1.0 );
      CPPUNIT_ASSERT_EQUAL( 180.0, s2.amount() );

      t_mSQ m1 = Metric::t_minute( 2.0 ) * Metric::t_second( 120.0 );
      CPPUNIT_ASSERT_EQUAL( 4.0, m1.amount() );

      t_mSQ m2 = Metric::t_minute( 2.0 ) * Metric::t_hour(1.0);
      CPPUNIT_ASSERT_EQUAL( 120.0, m2.amount() );

      t_hrSQ hr1 = Metric::t_hour( 1.0 ) * Metric::t_second( 7200 );
      CPPUNIT_ASSERT_EQUAL( 2.0, hr1.amount() );

   }
   ///Basic test with mass types
   void TestWithNonAtomicUnitUnitsMass()
   {
      using namespace Metric;
      namespace AU = AtomicUnit;
      typedef SOU::unitType< AU::Meter, 0, SOU::Time::AtomicUnit::second, -1, AU::gram, 0,AU::kelvin,0, AU::coulomb,0 > t_Hertz;
      
      Metric::t_gram g = 25.0;
      t_Hertz h = 3.0;

      Metric::t_gramPsec gps = g * h;
      CPPUNIT_ASSERT_EQUAL( 75.0, gps.amount() );
   }
   /// Test with the non-dimensional unit type to ensure that operator* still works with
   /// type of 0 diminsion.
   void TestWithNonDimension()
   {
      const t_Meter meter = 7.0;
      double y = 2.0;
      t_Meter high = meter * y;
      CPPUNIT_ASSERT_MESSAGE("testing with varible", high == 14.0 );
      CPPUNIT_ASSERT_MESSAGE("testing unitType*constant", 21.0 == meter * 3.0 );
      CPPUNIT_ASSERT_MESSAGE("testing constant * unitType", 3.0 * meter == 21.0 );

      double const x = 4;
      //t_Meter low = meter * tNoUnit(3.0);
      //low = meter * x;
      CPPUNIT_ASSERT_MESSAGE("testing with constant varible", meter * x == 28.0 );
      CPPUNIT_ASSERT_MESSAGE("test with a int", meter * 5 == 35.0 );
      CPPUNIT_ASSERT_MESSAGE("test with a float", meter * static_cast<float>(5.0) == 35.0 );
      CPPUNIT_ASSERT_MESSAGE("is this still allowed", 12.0 == x * 3 );

      CPPUNIT_ASSERT_MESSAGE("with zero", 0 == meter * 0.0 );
      CPPUNIT_ASSERT( 0 == 0 * meter );
      CPPUNIT_ASSERT( t_Meter(0) == meter * 0.0 );

      Metric::t_kilometer km = 3.0 * Metric::t_kilometer(1.0);
      CPPUNIT_ASSERT_EQUAL( 3.0, km.amount() );
      km = Metric::t_kilometer(1.0) * 3;
      CPPUNIT_ASSERT_EQUAL( 3.0, km.amount() );
      CPPUNIT_ASSERT( Metric::t_kilometer(3.0) == 3.0 * Metric::t_kilometer(1.0) );
   }

   /// Test with a multiplication after an subtraction
   void TestWithSubinside()
   {
      typedef Metric::t_second second;
      second Tmin = 55.5;
      second Tmax = 105.5;
      second Topt = Tmin + 0.7 * ( Tmax - Tmin );
      CPPUNIT_ASSERT_DOUBLES_EQUAL( 90.5, Topt.amount(), 0.00001 );
   }
   /// MultiplyFirst suite
  CPPUNIT_TEST_SUITE( MultiplyFirst );
  CPPUNIT_TEST( TestAssignment );
  CPPUNIT_TEST( TestMul_Result );
  CPPUNIT_TEST( TestWithCube );
  CPPUNIT_TEST( TestChaining );
  CPPUNIT_TEST( TestALLTYPES_THE_SAME );
  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsLength );
  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsTime );
  CPPUNIT_TEST( TestWithNonAtomicUnitUnitsMass );
  CPPUNIT_TEST( TestWithNonDimension );
  CPPUNIT_TEST( TestWithSubinside );
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( MultiplyFirst );

///class template to test multiplation operator against any different type of different
///diminsions in their quantity
template
< int PROD /// The product of the two arguments
, int MUL1 /// Argument type 1
, int MUL2 /// Argument type 2
>
class SI_Multiply : public CppUnit::TestFixture
{
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

   t_1 * m_1; /// Argument one
   t_2 const * m_2;  /// Argument two
   t_3 * m_3; /// The product of the two arguments

	double const m_delta;

public:
	SI_Multiply() : m_delta( 0.0000001 ){}

   void setUp()
   {
      m_1 = new t_1( 3.0 );
      m_2 = new t_2( 4.0 );
      m_3 = new t_3( 12.);
   }
   void tearDown()
   {
      delete m_1;
      delete m_2;
      delete m_3;
   }
private:
   /// Test the result type and shows that the result type is working correctly.
   void TestMul_Result()
   {
      using namespace SOU::operators;
      Mul_Result<t_1, t_2> sq_m( *m_1, *m_2 );
      CPPUNIT_ASSERT_MESSAGE("testing the expression template for mult", sq_m.result() == *m_3 );

      Mul_Result<t_1, t_2> const sq_m2( *m_1, *m_2 );
      CPPUNIT_ASSERT_MESSAGE("testing the expression template for mult", sq_m2.result() == *m_3 );
   }
   /// First test with operator*() and shows that it is working correctly
   void Test2()
   {
      // these test call internally Mul_Result
      t_3 prod = *m_1 * *m_2;
      CPPUNIT_ASSERT( prod == *m_3 );
      CPPUNIT_ASSERT( *m_3 == *m_1 * *m_2 );

      *m_3 = *m_1 * *m_2;
      CPPUNIT_ASSERT( *m_3 == 12.0 );

      CPPUNIT_ASSERT_MESSAGE("some chaining", *m_1 * *m_3 == *m_1 * *m_1 * *m_2 );
      CPPUNIT_ASSERT_MESSAGE("some chaining", *m_1 * *m_3 * *m_2 == *m_1 * *m_1 * *m_2 * *m_2 );
      CPPUNIT_ASSERT_MESSAGE("some chaining", (*m_1 * *m_3) * *m_2 == *m_1 * (*m_1 * *m_2) * *m_2 );
      CPPUNIT_ASSERT_MESSAGE("some chaining", *m_1 * (*m_3 * *m_2) == (*m_1 * *m_1) * (*m_2 * *m_2) );

   }
   /// Test operator*() with scalar values.
   void TestWithScaler()
   {
      CPPUNIT_ASSERT( 12.0 == *m_1 * 4.0 );
      CPPUNIT_ASSERT( t_1(12.0) == *m_1 * 4.0 );
      CPPUNIT_ASSERT( t_1(12.0) == 4.0 * *m_1 );

      CPPUNIT_ASSERT( 16.0 == *m_2 * 4.0 );
      CPPUNIT_ASSERT( t_2(16.0) == *m_2 * 4.0 );
      CPPUNIT_ASSERT( t_2(16.0) == 4.0 * *m_2);

      CPPUNIT_ASSERT( 48.0 == *m_3 * 4.0 );
      CPPUNIT_ASSERT( t_3(48.0) == *m_3 * 4.0 );
      CPPUNIT_ASSERT_MESSAGE("with some chaining", t_3(48.0) == *m_3 * 2.0 * 2.0 );
      CPPUNIT_ASSERT_MESSAGE("with some chaining", t_3(48.0) == 2.0 * *m_3 * 2.0 );
      CPPUNIT_ASSERT_MESSAGE("with some chaining", t_3(48.0) == 2.0 * 2.0 * *m_3 );

	  /// Test with integers
      CPPUNIT_ASSERT( 12 == *m_1 * 4 );
      CPPUNIT_ASSERT( t_1(12) == *m_1 * 4 );
      CPPUNIT_ASSERT( t_1(12) == 4 * *m_1 );

      CPPUNIT_ASSERT( 16.0 == *m_2 * 4 );
      CPPUNIT_ASSERT( t_2(16.0) == *m_2 * 4 );
      CPPUNIT_ASSERT( t_2(16.0) == 4 * *m_2);

      CPPUNIT_ASSERT( 48.0 == *m_3 * 4 );
      CPPUNIT_ASSERT( t_3(48.0) == *m_3 * 4 );
      CPPUNIT_ASSERT_MESSAGE("with some chaining", t_3(48.0) == *m_3 * 2 * 2.0 );
      CPPUNIT_ASSERT_MESSAGE("with some chaining", t_3(48.0) == 2 * *m_3 * 2 );

   }
   /// Have chaining with scalar values. Inside of a for-loop
   void TestChainWithScaler()
   {
      for( double x = 2.0; x < 12.0; x += 1.3 )
      {
         t_3 arg1 = *m_3 *x*x;
         t_3 arg2 = (*m_1*x) *( *m_2 * x);
         CPPUNIT_ASSERT_DOUBLES_EQUAL( arg1.amount(), arg2.amount(), 0.00001 );
         //CPPUNIT_ASSERT_EQUAL(*m_3 *x*x, (*m_1*x) *( *m_2 * x) );
      }
   }

   /// test operator*=()
   void TestMultipleAssign()
   {
		*m_3 *= 2.0;
		CPPUNIT_ASSERT_EQUAL( 24.0, m_3->amount() );

		*m_3 *= 0.5;
		CPPUNIT_ASSERT_EQUAL( 12.0, m_3->amount() );

   }

   /** Test A_Trait<int,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<int,T2>
	*/
   void TestMultipleInt()
   {
	   int const x = 2;
	   t_1 res1 = *m_1 * x;
	   t_1 const res2 = x * *m_1;

	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res1.amount(), m_delta );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res2.amount(), m_delta );
   }

   /** Test A_Trait<unsigned,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<unsigned,T2>

	When @code SystemOfUnits::operators::A_Trait<unsigned,T2> @endcode was commented out the below method failed to
	compile.
	*/ // @code meter z = 3.0 * y; @endcode
   void TestMultipleUnsigned()
   {
	   unsigned const x = 2;
	   t_1 res1 = *m_1 * x;
	   t_1 const res2 = x * *m_1;

	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res1.amount(), m_delta );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res2.amount(), m_delta );
   }

   /** Test A_Trait<float,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<float,T2>
	*/
   void TestMultipleFloat()
   {
	   float const x = 2.000;
	   t_1 res1 = *m_1 * x;
	   t_1 const res2 = x * *m_1;

	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res1.amount(), m_delta );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res2.amount(), m_delta );
   }

   /** Test A_Trait<short,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<short,T2>
	*/
   void TestMultipleShort()
   {
	   short const x = 2;
	   t_1 res1 = *m_1 * x;
	   t_1 const res2 = x * *m_1;

	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res1.amount(), m_delta );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res2.amount(), m_delta );
   }

   /** Test A_Trait<short,T2> template created from macro.  Test needs to be in class template 
   to prove that T_Trait handles the different Types
    @see SystemOfUnits::operators::A_Trait<short,T2>
	*/
   void TestMultipleLong()
   {
	   long const x = 2;
	   t_1 res1 = *m_1 * x;
	   t_1 const res2 = x * *m_1;

	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res1.amount(), m_delta );
	   CPPUNIT_ASSERT_DOUBLES_EQUAL( 6.0, res2.amount(), m_delta );
   }

   CPPUNIT_TEST_SUITE( SI_Multiply );
   CPPUNIT_TEST( TestMul_Result );
   CPPUNIT_TEST( Test2 );
   CPPUNIT_TEST( TestWithScaler );
   CPPUNIT_TEST( TestMultipleAssign );
   CPPUNIT_TEST( TestChainWithScaler );
   CPPUNIT_TEST( TestMultipleInt );
   CPPUNIT_TEST( TestMultipleUnsigned );
   CPPUNIT_TEST( TestMultipleFloat );
   CPPUNIT_TEST( TestMultipleShort );
   CPPUNIT_TEST( TestMultipleLong );
   CPPUNIT_TEST_SUITE_END();
};

typedef SI_Multiply<2,1,1> t_myMul;
CPPUNIT_TEST_SUITE_REGISTRATION( t_myMul );

typedef SI_Multiply<2,2,0> t_myMul1;
CPPUNIT_TEST_SUITE_REGISTRATION( t_myMul1 );

typedef SI_Multiply<3,2,1> t_Mul2;
CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul2 );

typedef SI_Multiply<5,2,3> t_Mul3;
CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul3 );

typedef SI_Multiply<2,-3,5> t_Mul4;
CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul4 );

typedef SI_Multiply<-2,3,-5> t_Mul5;
CPPUNIT_TEST_SUITE_REGISTRATION( t_Mul5 );
// }

// Copyright © 2005-2015 "Curt" Leslie L. Martin, All rights reserved.
// curt.leslie.lewis.martin@gmail.com
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

