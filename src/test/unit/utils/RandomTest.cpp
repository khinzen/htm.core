/* ---------------------------------------------------------------------
 * Numenta Platform for Intelligent Computing (NuPIC)
 * Copyright (C) 2013, Numenta, Inc.  Unless you have an agreement
 * with Numenta, Inc., for a separate license for this software code, the
 * following terms and conditions apply:
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero Public License for more details.
 *
 * You should have received a copy of the GNU Affero Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 *
 * http://numenta.org/licenses/
 * ---------------------------------------------------------------------
 */

/**
 * @file
 */

#include <fstream>
#include <gtest/gtest.h>
#include <nupic/ntypes/MemStream.hpp>
#include <nupic/os/Env.hpp>
#include <nupic/utils/LoggingException.hpp>
#include <nupic/utils/Random.hpp>
#include <sstream>
#include <vector>

using namespace nupic;
using namespace std;

TEST(RandomTest, Seeding) {
  {
  Random r;
  auto x = r.getUInt32();
  ASSERT_TRUE(x != 0);
  }

  // test getSeed
  {
    Random r(98765);
    ASSERT_EQ(98765U, r.getSeed());
  }

  { // seed & equals
  Random r1(1); 
  Random r2(2);
  ASSERT_NE(r1.getUInt32(), r2.getUInt32());
  ASSERT_NE(r1, r2) << "Randoms with different seed must be different";

  Random r1b(1);
  ASSERT_NE(r1, r1b) << "different steps";
  auto x = r1b.getUInt32();
  ASSERT_EQ(r1, r1b) << "Randoms with same seed must be the same." << x; 
  }

  { //MAX_INT seed
  Random r(-1);
  ASSERT_EQ(r(), 419326371u);
  }

}


TEST(RandomTest, CopyConstructor) {
  // test copy constructor.
  Random r1(289436);
  for (int i = 0; i < 100; i++)
    r1.getUInt32();
  Random r2(r1); //copy

  UInt32 v1, v2;
  for (int i = 0; i < 100; i++) {
    v1 = r1.getUInt32();
    v2 = r2.getUInt32();
    ASSERT_EQ(v1, v2) << "copy constructor";
  }
}


TEST(RandomTest, OperatorEquals) {
  // test operator=
  Random r1(289436);
  for (int i = 0; i < 100; i++)
    r1.getUInt32();
  Random r2(86726008);
  for (int i = 0; i < 100; i++)
    r2.getUInt32();

  r2 = r1;
  UInt32 v1, v2;
  for (int i = 0; i < 100; i++) {
    v1 = r1.getUInt32();
    v2 = r2.getUInt32();
    ASSERT_EQ(v1, v2) << "operator=";
  }
}


TEST(RandomTest, SerializationDeserialization) {
  // test serialization/deserialization
  Random r1(862973);
  for (int i = 0; i < 100; i++)
    r1.getUInt32();

  EXPECT_EQ(r1.getUInt32(), 2276275187u) << "Before serialization must be same";
  // serialize
  OMemStream ostream;
  ostream << r1;

  // print out serialization for debugging
  std::string x(ostream.str(), ostream.pcount());
//  NTA_INFO << "random serialize string: '" << x << "'";
  // Serialization should be deterministic and platform independent
  const std::string expectedString = "random-v2 862973 2265616446 2898581363 2833359659 3467106067 145734619 1191271442 3040813803 3630726205 2997769232 4142073884 2225658588 1071133121 2983491040 825194345 1389047388 1974804089 3378752625 750328973 2770629090 2604943675 2882186211 2515412243 1507462006 76738883 3412772496 1821076213 1103705666 1081871912 413418057 3111917938 2156864172 57347287 1469348556 378207249 3185052577 2265836208 359500198 528468897 3239223391 213367904 3597229177 497149564 283516840 2263451079 2278338648 1969906370 3583819797 533808602 943786735 3311758199 1991746911 3214290444 1292007602 2786728570 42617411 2490802642 49477094 4081300482 68756960 3047298923 3544028603 3329922450 2659629787 3819622849 499165220 3175570531 2731174570 1085481887 939601038 493616696 2269965728 2518341742 3094986386 2495406972 574334327 2687484 1499379339 2299926591 1702006517 1235676509 1210948961 3883174087 984058052 3673317090 2979204124 3720696549 263369462 3493839059 270266445 1231945499 3404943749 1782248405 3447029100 3207831401 2867469182 1340949376 673984061 162358452 3969733705 1792583697 513983040 1128014950 2579186209 595552031 726440413 583527775 1564306696 3663842251 707501588 718573947 2051837945 2927507601 87561163 1243651263 4033298256 1788918248 3520381552 3728842522 1825374401 2210508037 2606637923 2440828083 3619059805 3432574665 1475863713 3512864323 1858224655 4186962198 822961771 912926586 599870240 1327255754 4155764817 2596268183 500920676 81207912 49977262 1626508775 1406379588 3075899526 2790708788 4090448281 3418383958 1107584620 3504279682 64934008 2521892859 2487961275 727567728 2716178415 2274671612 3743636034 373259764 861243070 635882864 3182325975 89043456 1982448685 1885851116 2228760916 1067227619 4128382718 1876378849 2840558374 2065480143 2098549184 3886656629 1575250774 130178994 2443101603 1439982710 3388483156 1597147774 1868957660 942584307 2010730258 514205256 60897671 2624707427 3116713247 3505762959 1537990040 838402232 1589055397 2378279645 3282537970 3189443050 2309769971 657959844 533463637 2157041075 3313733236 3298143271 1401848587 1137915288 4162949419 1798919392 3224532970 594519575 2896283711 3145350025 1161204359 784148432 2297470419 2520919998 844843096 2298951915 1595523773 725151170 3553486598 2768109714 2424717486 3610481649 3953608661 1024372366 2002846931 2167856984 859646068 654670832 2516617463 2874529517 720769921 3584702908 1913289350 3529298479 3059528253 1234764652 1752486085 1707076519 808582024 4274130177 2411952964 914131934 663586455 3884341322 941241300 3803979212 4098862640 1924827754 3386667370 38674164 2616816948 2128456998 2663235297 3308404989 2942007652 555018941 3494580695 3315973131 128631596 3786342136 2576701127 3706739707 913551821 1316211125 938705976 2358415802 1951784947 4086964590 823935977 718332383 1090450846 681550988 749634229 756450583 2075339141 4124946342 3347637786 3005993526 727913464 3181507853 1229318358 783113737 2738214446 485316697 1632713787 821904443 1842218453 1395467441 1112966020 1718232730 3637558569 2344242555 1306899248 649201340 4197875742 1546899867 3475922336 99350943 1579664774 2232315698 3944252485 372140340 3781519882 2457074264 3909812594 1954220937 1061367907 1980758711 4135117515 516965136 3447228459 2895442277 1015541008 2500969549 709495309 3549656051 4248681823 1394387527 1151829365 2313028956 2254040206 2928105643 2685244988 403656845 2466767271 733334990 2074947840 2232394892 4001919762 4029082375 2939016569 3718445883 4067409103 2122885125 1053971027 329346235 3595611474 1030363317 1994904783 4169471573 2184301347 3635022534 1084524621 1764039412 1132501369 1539239820 4244583656 3568569750 2574045963 2054489127 667833653 1738679080 3552775196 916384104 250244680 3970991117 1703630161 505148739 203203077 3293832556 1496187240 1141213025 3256089060 815038547 3824587839 1395980461 3688653100 2802489240 3630780420 4091679260 2485829765 1114888235 102961035 3636324727 1741532326 2324267538 1512759768 1937726353 873619280 3286258405 1297588487 1030596503 1658569591 1203122545 3225713149 715763750 387198014 4233618083 2870989342 2561121222 1857590349 1580765539 1319332754 3865218472 4006818502 2434031433 12807888 4003301738 638570349 1639927709 2763589471 1006729725 3951962531 3892154298 1182836018 1435806679 3005762594 1612645397 90602237 3047735569 2614885817 3634535263 1593343873 3977575914 3059848806 2265550952 1823256097 3543920422 4251264312 2040300894 1756266016 821625008 3831087793 504239258 3054649899 1311201581 2793904794 3872358341 1158727073 1597285801 893407162 3780949979 804717065 1735605492 1850062210 1521915609 3940994919 3501990628 3143843002 3195862304 178753288 459876256 881992279 4178134666 910752 3856097585 574199821 2844698208 2140549626 1585976714 142373843 355357199 1223041094 191737282 2338137968 2062923741 2710781796 3319089366 3837627445 1967771431 4010541128 3323326446 3395356519 1643659775 1266466145 1976007314 2413260429 4116118141 3537535921 2635085854 3713201823 1297219818 1445627395 279775602 1744034992 1837838174 1280598984 955072637 889334104 1193619512 443813187 3174489216 2035936251 4334072 1149311108 1473569210 2311687034 3872942998 1534895283 1973141532 37679540 2408421041 2778366810 471957145 247735917 3920765714 3705856063 3998081166 1912212919 2230282838 2059793168 3698575843 3432281426 3312934388 4046118773 4248513829 1716068872 576199365 3262645776 498445289 1787237505 1806340829 1925965092 3815152701 3639010060 1374016222 1068493439 2049665441 2443209513 2415233361 2208204491 466523244 334943558 1346821197 3091970350 3715944241 1353407951 3541224293 3815931728 1171325214 2178720068 1505189564 633006559 3249822949 759889160 1391072374 1357742599 775670850 3866791257 4155635669 1889214961 2341476043 4201985051 2156226804 2214203720 123718977 3436568490 96753226 679075091 2659606616 3822905544 1380780110 3704429156 3410816742 2300757762 1318159834 3503627298 3635371904 553720441 1776825620 4205080704 1031620890 655341913 3606230176 1142313024 589625026 3574952813 3297246564 3226099933 3986909229 1818167680 4013353083 1018943338 3224336995 29106550 3942402895 2517791487 3875189392 3528589574 59757838 3232102139 3030714509 3272730476 1729016134 144685168 2599670757 785671418 3724227161 3498575620 3718934739 867570309 266852886 1314506399 1595186477 1948014485 2152031251 2517123528 2570423544 383275576 2688359154 3399669969 3316609503 2814155701 672160642 2601588109 3126276246 387989615 1544154976 1134437117 1589174726 3946229530 1877478163 485124005 44420014 3847982684 1497075108 3358944354 3528350838 1953179206 1521729519 2916925366 711908468 118076528 573207412 1270874671 3166474564 3933425079 2259647182 2818908223 2668728406 1539997687 2348823515 1444013000 101 endrandom-v2 ";
  EXPECT_EQ(expectedString, x) << "De/serialization";

  // deserialize into r2
  std::string s(ostream.str(), ostream.pcount());
  std::stringstream ss(s);
  Random r2;
  ss >> r2;

  // r1 and r2 should be identical
  EXPECT_EQ(r1, r2) << "load from serialization";
  EXPECT_EQ(r2.getUInt32(), 3537119063u) << "Deserialized is not deterministic";
  r1.getUInt32(); //move the same number of steps

  UInt32 v1, v2;
  for (int i = 0; i < 100; i++) {
    v1 = r1.getUInt32();
    v2 = r2.getUInt32();
    EXPECT_EQ(v1, v2) << "serialization";
  }
}


TEST(RandomTest, ReturnInCorrectRange) {
  // make sure that we are returning values in the correct range
  // @todo perform statistical tests
  Random r;
  UInt32 seed = r.getSeed();
  ASSERT_TRUE(seed != 0) << "seed not zero";
  int i;
  UInt32 max32 = 10000000;
  for (i = 0; i < 2000; i++) {
    UInt32 i32 = r.getUInt32(max32);
    ASSERT_TRUE(i32 < max32) << "UInt32";
    Real64 r64 = r.getReal64();
    ASSERT_TRUE(r64 >= 0.0 && r64 < 1.0) << "Real64";
  }
}

/*
TEST(RandomTest, getUInt64) {
  // tests for getUInt64
  Random r1(1);
  ASSERT_EQ(2469588189546311528u, r1.getUInt64())
      << "check getUInt64, seed 1, first call";
  ASSERT_EQ(2516265689700432462u, r1.getUInt64())
      << "check getUInt64, seed 1, second call";

  Random r2(2);
  ASSERT_EQ(16668552215174154828u, r2.getUInt64())
      << "check getUInt64, seed 2, first call";
  EXPECT_EQ(15684088468973760345u, r2.getUInt64())
      << "check getUInt64, seed 2, second call";

  Random r3(7464235991977222558);
  EXPECT_EQ(8035066300482877360u, r3.getUInt64())
      << "check getUInt64, big seed, first call";
  EXPECT_EQ(623784303608610892u, r3.getUInt64())
      << "check getUInt64, big seed, second call";
}
*/

TEST(RandomTest, getUInt32) {
  // tests for getUInt32
  Random r1(1);
  EXPECT_EQ(1791095845u, r1.getUInt32())
      << "check getUInt64, seed 1, first call";
  EXPECT_EQ(4282876139u, r1.getUInt32())
      << "check getUInt64, seed 1, second call";

  Random r2(2);
  EXPECT_EQ(1872583848u, r2.getUInt32())
      << "check getUInt64, seed 2, first call";
  EXPECT_EQ(794921487u, r2.getUInt32())
      << "check getUInt64, seed 2, second call";

  Random r3(7464235991977222558);
  EXPECT_EQ(1606095383u, r3.getUInt32())
      << "check getUInt64, big seed, first call";
  EXPECT_EQ(59943411, r3.getUInt32())
      << "check getUInt64, big seed, second call";
}


TEST(RandomTest, getReal64) {
  // tests for getReal64
  Random r1(1);
  EXPECT_DOUBLE_EQ(0.41702199853421701, r1.getReal64());
  EXPECT_DOUBLE_EQ(0.99718480836534518, r1.getReal64());

  Random r2(2);
  EXPECT_DOUBLE_EQ(0.43599490272719293, r2.getReal64());
  EXPECT_DOUBLE_EQ(0.18508208151559394, r2.getReal64());

  Random r3(7464235991977222558);
  EXPECT_DOUBLE_EQ(0.37394822188046489, r3.getReal64());
  EXPECT_DOUBLE_EQ(0.013956662969187988, r3.getReal64());
}


TEST(RandomTest, Sampling) {
  // tests for sampling

  const vector<UInt> population = {1u, 2u, 3u, 4u};
  Random r(17);

  {
    // choose some elements
    auto  choices = r.sample<UInt>(population, 2);
    EXPECT_EQ(3u, choices[0]) << "check sample 0";
    EXPECT_EQ(2u, choices[1]) << "check sample 1";
  }

  {
    // choose all elements
    vector<UInt> choices = r.sample<UInt>(population, 4);

    EXPECT_EQ(1u, choices[0]) << "check sample 0";
    EXPECT_EQ(2u, choices[1]) << "check sample 1";
    EXPECT_EQ(4u, choices[2]) << "check sample 2";
    EXPECT_EQ(3u, choices[3]) << "check sample 3";
  }

  //check population list remained unmodified
  ASSERT_EQ(1, population[0]) << "check sample p 0";
  ASSERT_EQ(2, population[1]) << "check sample p 1";
  ASSERT_EQ(3, population[2]) << "check sample p 2";
  ASSERT_EQ(4, population[3]) << "check sample p 3";

  {
    // nChoices > nPopulation
    EXPECT_THROW(r.sample<UInt>(population, 5), LoggingException) << "checking for exception from population too small";
  }
}


TEST(RandomTest, Shuffling) {
  // tests for shuffling
  Random r(1);
  UInt32 arr[] = {1u, 2u, 3u, 4u};
  const UInt32 exp[] = {4u, 1u, 3u, 2u};

  ASSERT_NO_THROW(r.shuffle(std::begin(arr), std::end(arr)));

  EXPECT_EQ(exp[0], arr[0]) << "check shuffle 0";
  EXPECT_EQ(exp[1], arr[1]) << "check shuffle 1";
  EXPECT_EQ(exp[2], arr[2]) << "check shuffle 2";
  EXPECT_EQ(exp[3], arr[3]) << "check shuffle 3";
}


/**
 * Test operator '=='
 */
TEST(RandomTest, testEqualsOperator) {
  Random r1(42), r2(42), r3(3);
  ASSERT_EQ(r1, r2);
  ASSERT_NE(r1, r3);
  ASSERT_NE(r2, r3);

  UInt32 v1, v2;
  v1 = r1.getUInt32();
  ASSERT_NE(r1, r2) << "one step diff";
  v2 = r2.getUInt32();
  ASSERT_EQ(r1, r2) << "synchronized steps";
  ASSERT_EQ(v1, v2);
}


TEST(RandomTest, testGetUIntSpeed) {
 Random r1(42);
 UInt32 rnd;
 const int RUNS = 10000000;
 for(int i=0; i<RUNS; i++) {
   rnd = r1.getUInt32(10000); //get random int [0..1M)
 }
 EXPECT_EQ(rnd, 9278u);
}
