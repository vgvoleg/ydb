// Copyright 2017 Google Inc. All Rights Reserved. 
// 
// Licensed under the Apache License, Version 2.0 (the "License"); 
// you may not use this file except in compliance with the License. 
// You may obtain a copy of the License at 
// 
//     http://www.apache.org/licenses/LICENSE-2.0 
// 
// Unless required by applicable law or agreed to in writing, software 
// distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and 
// limitations under the License. 
 
// Ensures each implementation of HighwayHash returns consistent and unchanging 
// hash values. 
 
#include "highwayhash/highwayhash_test_target.h" 
 
#include <stddef.h> 
#include <atomic> 
#include <cstdio> 
#include <cstdlib> 
#include <vector> 
 
#ifdef HH_GOOGLETEST 
#include "testing/base/public/gunit.h" 
#endif 
 
#include "highwayhash/data_parallel.h" 
#include "highwayhash/instruction_sets.h" 
 
// Define to nonzero in order to print the (new) golden outputs. 
#define PRINT_RESULTS 0 
 
namespace highwayhash { 
namespace { 
 
// Known-good outputs are verified for all lengths in [0, 64]. 
const size_t kMaxSize = 64; 
 
#if PRINT_RESULTS 
void Print(const HHResult64 result) { printf("0x%016lXull,\n", result); } 
 
// For HHResult128/256. 
template <int kNumLanes> 
void Print(const HHResult64 (&result)[kNumLanes]) { 
  printf("{ "); 
  for (int i = 0; i < kNumLanes; ++i) { 
    if (i != 0) { 
      printf(", "); 
    } 
    printf("0x%016lXull", result[i]); 
  } 
  printf("},\n"); 
} 
#endif  // PRINT_RESULTS 
 
// Called when any test fails; exits immediately because one mismatch usually 
// implies many others. 
void OnFailure(const char* target_name, const size_t size) { 
  printf("Mismatch at size %zu\n", size); 
#ifdef HH_GOOGLETEST 
  EXPECT_TRUE(false); 
#endif 
  exit(1); 
} 
 
// Verifies every combination of implementation and input size. Returns which 
// targets were run/verified. 
template <typename Result> 
TargetBits VerifyImplementations(const Result (&known_good)[kMaxSize + 1]) { 
  const HHKey key = {0x0706050403020100ULL, 0x0F0E0D0C0B0A0908ULL, 
                     0x1716151413121110ULL, 0x1F1E1D1C1B1A1918ULL}; 
 
  TargetBits targets = ~0U; 
 
  // For each test input: empty string, 00, 00 01, ... 
  char in[kMaxSize + 1] = {0}; 
  // Fast enough that we don't need a thread pool. 
  for (uint64_t size = 0; size <= kMaxSize; ++size) { 
    in[size] = static_cast<char>(size); 
#if PRINT_RESULTS 
    Result actual; 
    targets &= InstructionSets::Run<HighwayHash>(key, in, size, &actual); 
    Print(actual); 
#else 
    const Result* expected = &known_good[size]; 
    targets &= InstructionSets::RunAll<HighwayHashTest>(key, in, size, expected, 
                                                        &OnFailure); 
#endif 
  } 
  return targets; 
} 
 
// Cat 
 
void OnCatFailure(const char* target_name, const size_t size) { 
  printf("Cat mismatch at size %zu\n", size); 
#ifdef HH_GOOGLETEST 
  EXPECT_TRUE(false); 
#endif 
  exit(1); 
} 
 
// Returns which targets were run/verified. 
template <typename Result> 
TargetBits VerifyCat(ThreadPool* pool) { 
  // Reversed order vs prior test. 
  const HHKey key = {0x1F1E1D1C1B1A1918ULL, 0x1716151413121110ULL, 
                     0x0F0E0D0C0B0A0908ULL, 0x0706050403020100ULL}; 
 
  const size_t kMaxSize = 3 * 35; 
  std::vector<char> flat; 
  flat.reserve(kMaxSize); 
  srand(129); 
  for (size_t size = 0; size < kMaxSize; ++size) { 
    flat.push_back(static_cast<char>(rand() & 0xFF)); 
  } 
 
  std::atomic<TargetBits> targets{~0U}; 
 
  pool->Run(0, kMaxSize, [&key, &flat, &targets](const uint32_t i) { 
    Result dummy; 
    targets.fetch_and(InstructionSets::RunAll<HighwayHashCatTest>( 
        key, flat.data(), i, &dummy, &OnCatFailure)); 
  }); 
  return targets.load(); 
} 
 
const HHResult64 kExpected64[kMaxSize + 1] = { 
    0x907A56DE22C26E53ull, 0x7EAB43AAC7CDDD78ull, 0xB8D0569AB0B53D62ull, 
    0x5C6BEFAB8A463D80ull, 0xF205A46893007EDAull, 0x2B8A1668E4A94541ull, 
    0xBD4CCC325BEFCA6Full, 0x4D02AE1738F59482ull, 0xE1205108E55F3171ull, 
    0x32D2644EC77A1584ull, 0xF6E10ACDB103A90Bull, 0xC3BBF4615B415C15ull, 
    0x243CC2040063FA9Cull, 0xA89A58CE65E641FFull, 0x24B031A348455A23ull, 
    0x40793F86A449F33Bull, 0xCFAB3489F97EB832ull, 0x19FE67D2C8C5C0E2ull, 
    0x04DD90A69C565CC2ull, 0x75D9518E2371C504ull, 0x38AD9B1141D3DD16ull, 
    0x0264432CCD8A70E0ull, 0xA9DB5A6288683390ull, 0xD7B05492003F028Cull, 
    0x205F615AEA59E51Eull, 0xEEE0C89621052884ull, 0x1BFC1A93A7284F4Full, 
    0x512175B5B70DA91Dull, 0xF71F8976A0A2C639ull, 0xAE093FEF1F84E3E7ull, 
    0x22CA92B01161860Full, 0x9FC7007CCF035A68ull, 0xA0C964D9ECD580FCull, 
    0x2C90F73CA03181FCull, 0x185CF84E5691EB9Eull, 0x4FC1F5EF2752AA9Bull, 
    0xF5B7391A5E0A33EBull, 0xB9B84B83B4E96C9Cull, 0x5E42FE712A5CD9B4ull, 
    0xA150F2F90C3F97DCull, 0x7FA522D75E2D637Dull, 0x181AD0CC0DFFD32Bull, 
    0x3889ED981E854028ull, 0xFB4297E8C586EE2Dull, 0x6D064A45BB28059Cull, 
    0x90563609B3EC860Cull, 0x7AA4FCE94097C666ull, 0x1326BAC06B911E08ull, 
    0xB926168D2B154F34ull, 0x9919848945B1948Dull, 0xA2A98FC534825EBEull, 
    0xE9809095213EF0B6ull, 0x582E5483707BC0E9ull, 0x086E9414A88A6AF5ull, 
    0xEE86B98D20F6743Dull, 0xF89B7FF609B1C0A7ull, 0x4C7D9CC19E22C3E8ull, 
    0x9A97005024562A6Full, 0x5DD41CF423E6EBEFull, 0xDF13609C0468E227ull, 
    0x6E0DA4F64188155Aull, 0xB755BA4B50D7D4A1ull, 0x887A3484647479BDull, 
    0xAB8EEBE9BF2139A0ull, 0x75542C5D4CD2A6FFull}; 
 
const HHResult128 kExpected128[kMaxSize + 1] = { 
    {0x0679D1E884C28A7Cull, 0x2BCA2547F904748Dull}, 
    {0x7F3A39BCC2D897B9ull, 0x4A7E113CA064D91Full}, 
    {0x6AB34B92C5AB85BFull, 0xED7AC546689D76C2ull}, 
    {0xAC6AF8405A4A7DBEull, 0xD78FB7953256C3E1ull}, 
    {0x5A6E8CF789B86448ull, 0x834EF47C1BEDC218ull}, 
    {0x8EBFE0B573F425A3ull, 0xBCFCC410CB84325Aull}, 
    {0xA1E19717CAB8F1D6ull, 0x2AA50671881F877Dull}, 
    {0x0B595302950DA1ECull, 0x46932DE27204B388ull}, 
    {0x02FB033F200F89D4ull, 0xFEC3D7BB3B421F92ull}, 
    {0x0A5479D46CC1EADEull, 0x0C16A2D5A0F1C3DEull}, 
    {0xF759E41DDD621106ull, 0xB43D70116E004750ull}, 
    {0x980010BC36A4E98Full, 0x27479317AE00BBD1ull}, 
    {0x3BABF3B23761A379ull, 0xACCDC28E0256F326ull}, 
    {0x5780CD04269E142Eull, 0xBB70EE3F23BDEDA9ull}, 
    {0x4A401F1937E99EC3ull, 0x4B3D1385D6B4E214ull}, 
    {0x045C6EDE080E2CB0ull, 0x7327B45D2132DC89ull}, 
    {0x97E1624BEB1C1756ull, 0xB7137E1B69D45024ull}, 
    {0x31DBA8E3DB0BF012ull, 0x3E66E6A78A729B16ull}, 
    {0x34D6DF1B5D8AF2A7ull, 0x4F1A47FCBC39EB55ull}, 
    {0xE2C6BE2D47E5DCBCull, 0xD2FF85284E307C1Full}, 
    {0xDA681E06098EC892ull, 0x71AD98355019FED1ull}, 
    {0xC4FBD72B1F2FC30Bull, 0x327549B6C9FDEDD5ull}, 
    {0x14F429D1C20F0EB5ull, 0x228B40C92F3FA369ull}, 
    {0xF5C9535333206D01ull, 0xB6FC46FCCA65F9CCull}, 
    {0x3049FAD9DB729D2Dull, 0xB84C931C45F781EAull}, 
    {0x7C6FFE6F3706DC04ull, 0x4F94583806AE3C62ull}, 
    {0x9EF95EB28BE1CCE0ull, 0xAD9D5B96A0D15BFEull}, 
    {0x63D0ED54AF2985E6ull, 0xDFAFB1B6485C1B01ull}, 
    {0xA46C8A2FE498D46Cull, 0xF4DBAEC0FF03BAD6ull}, 
    {0xED978A0FBB3E5158ull, 0x060D144D57FBE6FDull}, 
    {0x53F1D80C8922E4E5ull, 0x1324880D932140C9ull}, 
    {0xDD363B03563870CEull, 0x0DFDB79F4F34184Bull}, 
    {0x4E702701AE65DB38ull, 0x1B67E0A2E2DBFB04ull}, 
    {0x240DA388551D0822ull, 0x2FF1BB584AC4BD61ull}, 
    {0x3FAFB8B7C26499ABull, 0x072516308E889132ull}, 
    {0x0AB452339406AB22ull, 0x751DBB7FF9472D42ull}, 
    {0x83BA782DB6EB1186ull, 0x4391544D9318DC29ull}, 
    {0x25077ECDAAB201E8ull, 0x695E0E95446D63A2ull}, 
    {0x1AF0BF12F91F17D4ull, 0x5BB8FF299368D22Cull}, 
    {0x338C09CBAF701E38ull, 0xA7D24D5E7C06DC78ull}, 
    {0x5AB58D6555D28B56ull, 0xE781413A9AE1310Full}, 
    {0xB0281CD10BCA7B89ull, 0xF49873B45C0F7274ull}, 
    {0x67EEBD6D71E57B06ull, 0x9421CB1DB54EEDDFull}, 
    {0x00DAB867E37EDA65ull, 0x6477E454191E213Full}, 
    {0x9AF9C4817C24C82Eull, 0xAE3A73522F311EEBull}, 
    {0xD8A334E30D23C6E6ull, 0xAF57EF86CCCF12FFull}, 
    {0x0353A48FC9E139DDull, 0x27D5626170A7DD0Full}, 
    {0x0DA12E888EB61876ull, 0x67B17DF10CB365CDull}, 
    {0x967CD764883A5E85ull, 0x570D7C9A774A6AB4ull}, 
    {0xA8DF13980C81E533ull, 0x9C33FE4797F87F1Aull}, 
    {0xCABB59F53AE75FF2ull, 0x6D25512E77172E7Aull}, 
    {0xB24E7F0C7DA62BE7ull, 0x2442F94890F57D89ull}, 
    {0x7DCBA0A5B9689BBDull, 0x700FC8D13DA4CC60ull}, 
    {0x1E8E014B97A9F828ull, 0xF858EFCA33E8A502ull}, 
    {0x4DAF4E31F34D10C7ull, 0x47E382D0A5A8C613ull}, 
    {0x577CAB4EF626BB28ull, 0xF6ED27E594C5795Full}, 
    {0x989188C958586C96ull, 0x8B3A2CB0D5B48FD9ull}, 
    {0x13CC58F5A076C088ull, 0x932A0FD21D4B422Cull}, 
    {0xD067380DAD885647ull, 0xC1020E396B31BB4Aull}, 
    {0x47D05A73072758D0ull, 0x5CF6075A0AEB5D78ull}, 
    {0x54441D7AE94E2D4Eull, 0x3B4F67953ABD3EA4ull}, 
    {0xEDD4250C3733EEBCull, 0x26E365AA1167C723ull}, 
    {0x92D02D2A641DA598ull, 0x3DAF5EB24A0C2A94ull}, 
    {0xAE6CF7FE2D76CA56ull, 0xC7918532A42D2F5Dull}, 
    {0xAD24762A08D96F1Bull, 0x729083EC59FA8DF7ull}}; 
 
const HHResult256 kExpected256[kMaxSize + 1] = { 
    {0xC6DC0C823434863Full, 0x6A42CCB644CBFAD9ull, 0x18DEF6A60EA5D873ull, 
     0x3596F663D00D1225ull}, 
    {0x00518B3D2BD22424ull, 0xE5791619BF612E97ull, 0xF4DAF07017FAF99Dull, 
     0xE36AE62C5509B5D6ull}, 
    {0x81021CC5067D8526ull, 0xBEEFC1BC87A6911Aull, 0xE2AEC605F80657FEull, 
     0x3C6576B5DF982327ull}, 
    {0x118D72C0B5DB2C70ull, 0x0BE2E64BF538CA74ull, 0x667B33FE41DDAA74ull, 
     0xB6199539303E13E1ull}, 
    {0x4AC9B8B2E4FD873Bull, 0xDE0FE265A45FFC97ull, 0x1FC1476F896ADA3Bull, 
     0x7680B4AE30B371E7ull}, 
    {0x518ABC6B5E88214Full, 0xFD62A05B2B06026Bull, 0x9C978E8B38DBE795ull, 
     0x41412401886FF054ull}, 
    {0x2DEDEF0832BEA7D9ull, 0x44EFE0AEAB7944FCull, 0x09AA7C9374A1E980ull, 
     0x714DB8B507C507FBull}, 
    {0x6FA2135DE3D3D3AAull, 0xC0EEA9A890E36156ull, 0xFAC1DB8C817DB095ull, 
     0x7B42789096836327ull}, 
    {0x27257C518B1FFC5Cull, 0x26CC8E669DA1AB0Full, 0xCD7B17C661A0A680ull, 
     0x31D0A7EC0AA3B9BFull}, 
    {0xB91869900A1AF26Cull, 0x95B0D74B7FF20B43ull, 0x2A6CABF6F931B575ull, 
     0x69734DC9E66A1965ull}, 
    {0xDD7DA31F5C4DD30Full, 0x08940D249A0A7B69ull, 0xAE7D3AD1C5EA81F2ull, 
     0x96701DB5C6602B21ull}, 
    {0x2E4A230847E64687ull, 0xF96176C38E48B038ull, 0x9ED0B88A3026E1BCull, 
     0x9AAB5DCA46FCFE19ull}, 
    {0x3E5CF04BFBAC2642ull, 0x591A3581001709DFull, 0xA0288F5FA63C10A2ull, 
     0x85B94D3641A2C108ull}, 
    {0x454A95FAD8901350ull, 0x5546E8E75D2AC833ull, 0xCF5FF2ACB4B5F2C1ull, 
     0x14F314318028D62Eull}, 
    {0x0DED251FB81F34A9ull, 0xC42111DB31618AA6ull, 0xC1C3352B70B00C5Dull, 
     0xDC8947DBC398F0C2ull}, 
    {0xC591A100AB4E9E72ull, 0x4CCFD2A7B0D8D911ull, 0x6FEDFDDE1BA3F770ull, 
     0x03E5C5A2F6E708A1ull}, 
    {0x537C42CC5E7B448Aull, 0xA7343E04249B2231ull, 0x2CB51D697EFE9B6Dull, 
     0x589D83141A699A97ull}, 
    {0x3F7E6EA60343B870ull, 0x4E27E907E296D4D7ull, 0x87525BF1AABBF794ull, 
     0x6B03C4DC206EC628ull}, 
    {0x741BA4D7A856E03Cull, 0x3798422CB64C9AFAull, 0xB1D89C9720D33FDDull, 
     0x08DE607FC4E3B5C3ull}, 
    {0x77D77342C85BA466ull, 0xA01C603C58F6D97Eull, 0x342AF0A7309EA4EAull, 
     0x9C958EB3F6A64B94ull}, 
    {0x9EDCADDD1FFC763Full, 0xBD9BAA6E9BE936EFull, 0xAAB0F78F1A4A94F7ull, 
     0xE71D9CA601DA4C02ull}, 
    {0xE3AA0D0A422BF888ull, 0x07734C8173411035ull, 0x8A085019DE545AF6ull, 
     0xBC3C520B1221A779ull}, 
    {0x16170C02C5E5439Dull, 0x45C6004513BFC174ull, 0x35CF3AD65D225EC8ull, 
     0xE10BAA702D37C90Eull}, 
    {0x6BD63B47EA43ABC6ull, 0xCC08BE8A651E24C0ull, 0xB564F0FC6FF8998Aull, 
     0x3EE409A34232E589ull}, 
    {0xD6CEE5574355BB81ull, 0x8E31FF40B271A16Dull, 0xC3ECEDBEEACCCAE9ull, 
     0x19386CD3A23B92E9ull}, 
    {0x32475E05D248DBB1ull, 0xF2396A122830E72Cull, 0xB88395678C0DB899ull, 
     0x8BD410A22A247066ull}, 
    {0x0BFA3B3C4775EB43ull, 0x496596C36FB2A200ull, 0xA00F533EF150D7DDull, 
     0xB5D70BBCABB572C4ull}, 
    {0x932B0ED33ED691B1ull, 0xB58394EDCEA3C53Dull, 0xB935E0786B132755ull, 
     0x3E0998322B3F74BAull}, 
    {0xE21F2CE1BDD156A7ull, 0x764518A56E1363B5ull, 0x461251D3EC39B93Full, 
     0x33C1FE46C9664CC4ull}, 
    {0x8ABD3F6184C9CD7Dull, 0x8195816637017FC0ull, 0x284B3E93524765DEull, 
     0x56147BDBA9362D0Eull}, 
    {0x1F050672342807B6ull, 0x9B0AD1091A83910Dull, 0xF23AD4A58C3B1E21ull, 
     0xCC986EC0BEA16781ull}, 
    {0x053164DEF96B10CEull, 0x1D5ADA15E36D8F6Cull, 0x06FB43534C0472EFull, 
     0x021C0ED1FDEA0948ull}, 
    {0xF62BA4C5A665E602ull, 0x490D89FD89430C56ull, 0x18F423BE8A9B7E3Cull, 
     0x769E5DDA4DCAC619ull}, 
    {0xDABD25FAF07A6684ull, 0xACA85CD21536B927ull, 0xAC05E050B4E3D3D1ull, 
     0xBE427B2475CCD981ull}, 
    {0x89A2B35A34F89F8Cull, 0x1A0E51B2875D34E6ull, 0xBA573CF45E123919ull, 
     0x1C50815B08F1138Aull}, 
    {0x3390CCBE60F2AFF7ull, 0xD9E2D245643E79C2ull, 0x1104A78F85D3CDF5ull, 
     0x7E55F38F9C53A58Full}, 
    {0xC189AE1A9D456C0Eull, 0x06AA4C3D4204A40Full, 0x4B383405A9D451A9ull, 
     0x7EA34CBCAEF0C31Eull}, 
    {0xB45FA7CC19AE4DDFull, 0x306C418E9BA67420ull, 0xDF16D80D4D48C096ull, 
     0xD3169E50BC8D75CCull}, 
    {0x5894367013710C89ull, 0xD39EE6D584E76AF3ull, 0x5C55A414BCDDE505ull, 
     0x8FA97D561CB174BFull}, 
    {0x87355749D59F39DDull, 0x26B8B311E72C50F4ull, 0x1911A8CBCE53E37Bull, 
     0x5C256452C39B95F6ull}, 
    {0x8B9E87C9ABC82821ull, 0x12A5FC06B69CDC2Dull, 0xF95104FF805E5E1Dull, 
     0xE5D4D2257AD5592Eull}, 
    {0x5A89242B02E1E048ull, 0x771602AAD1880A7Eull, 0x0F34507608387843ull, 
     0x7AFB45F3EA4F0F24ull}, 
    {0x3BE3800150FDDE00ull, 0x7871908FF91AD81Aull, 0xA00E07F351BB15C1ull, 
     0x429658E7FD10D11Aull}, 
    {0x2B2B1A6CD1BA454Cull, 0xF19E8CA5C022308Aull, 0xAEFA0EB6F7C3CF74ull, 
     0x21F4330A5258E7C7ull}, 
    {0xD1C806622910A9BEull, 0xFE224EF598F541B1ull, 0xB95A435AEC4DD849ull, 
     0xD942A277AB57E68Eull}, 
    {0x16BF7116E8D2B328ull, 0xB37DC98EA931FC13ull, 0x18E8859A592C8C11ull, 
     0x11590F16C4C61716ull}, 
    {0xD046122D4C7B24AEull, 0xBD0899DFD7345611ull, 0x91AAECB50DE6DFF9ull, 
     0x6EDC4896BAA90FFAull}, 
    {0x2FE97B8135EA956Dull, 0xFBA50900FB4EF23Cull, 0x0BC907363F7EA368ull, 
     0xA5C982D3094BCEE2ull}, 
    {0x247BFB5BA3A0F245ull, 0x6ACBDD4AFFDB03EBull, 0xA4237427D373B619ull, 
     0xFA9C041D302B728Cull}, 
    {0xF93109909D6B80EFull, 0xD1321A6BEE302794ull, 0xD63E1E7985C458D3ull, 
     0x644CD44F6C6FDE95ull}, 
    {0xD0522C663FBE65B0ull, 0x78F366F302EA33F5ull, 0xB9ED66D1CB87C891ull, 
     0x0CEB2298BA9D1C1Aull}, 
    {0x60D60E9B569264E8ull, 0xE34447A5741417EAull, 0x04522108BDF3AFC3ull, 
     0x90F4FE2D585B25FAull}, 
    {0xAF411662AAB81B12ull, 0x3AD58EBBA1BA2F39ull, 0x73E0E8EB5879E37Dull, 
     0xCE0E8F8F613D3FC5ull}, 
    {0xCA756CB9E1FDF1C6ull, 0x89731D81712D34BDull, 0xBF520B2D830959C2ull, 
     0xD35ED12BB24CE9EFull}, 
    {0x5FB2B65ABF038045ull, 0x3F2D32F8532E14D6ull, 0x06443CC95CDD58C8ull, 
     0x30FC6FBE8CCE8EB8ull}, 
    {0x94A9774F02848D73ull, 0x83F9AFC4C0B48768ull, 0xDB7BF5FBD9B25A26ull, 
     0x7F7D50266FFA639Bull}, 
    {0x352A775C646259DDull, 0xB2B532B472539832ull, 0x9981AE050A2FB38Cull, 
     0xE13641E804F6DC00ull}, 
    {0x080E005A04E73352ull, 0x0314F6EA196A210Cull, 0x29EA80869CE307A4ull, 
     0x4FABEB9ADE04BE00ull}, 
    {0x5674A4A533335ADFull, 0x3C7C0650FF6C585Bull, 0x384E4F8246446812ull, 
     0xAE2DADA5E0EB6D81ull}, 
    {0xB6CE794A89B0A1F7ull, 0x0DC2B87EC9473CDDull, 0x349A006CA2899C88ull, 
     0x4B411CB7DF6BF33Cull}, 
    {0xD79BB5606CE6BDAFull, 0x4040EA447818A5C1ull, 0x53D58C5710475284ull, 
     0x3DA8730E092608BAull}, 
    {0x5900A2DAA12E085Cull, 0x80D490C510C493DDull, 0x4BDF17B0247C8D1Bull, 
     0xA8649490D6CFCE67ull}, 
    {0xFBDAB07B10180D47ull, 0xED6C196BDC43E292ull, 0xE7D494077FA2791Dull, 
     0xC7108D4FD01BBF85ull}, 
    {0x4365D6236E6AE467ull, 0xB3D540909D4308A5ull, 0xE38207ABD4588D68ull, 
     0xBBD42849A8C92313ull}, 
    {0x064DB5FE415126F5ull, 0x248AF8FB29A9C595ull, 0x508633A742B3FFF7ull, 
     0x24CFDCA800C34770ull}}; 
 
void RunTests() { 
  // TODO(janwas): detect number of cores. 
  ThreadPool pool(4); 
 
  TargetBits tested = ~0U; 
  tested &= VerifyImplementations(kExpected64); 
  tested &= VerifyImplementations(kExpected128); 
  tested &= VerifyImplementations(kExpected256); 
  // Any failure causes immediate exit, so apparently all succeeded. 
  HH_TARGET_NAME::ForeachTarget(tested, [](const TargetBits target) { 
    printf("%10s: OK\n", TargetName(target)); 
  }); 
 
  tested = ~0U; 
  tested &= VerifyCat<HHResult64>(&pool); 
  tested &= VerifyCat<HHResult128>(&pool); 
  tested &= VerifyCat<HHResult256>(&pool); 
  HH_TARGET_NAME::ForeachTarget(tested, [](const TargetBits target) { 
    printf("%10sCat: OK\n", TargetName(target)); 
  }); 
} 
 
#ifdef HH_GOOGLETEST 
TEST(HighwayhashTest, OutputMatchesExpectations) { RunTests(); } 
#endif 
 
}  // namespace 
}  // namespace highwayhash 
 
#ifndef HH_GOOGLETEST 
int main(int argc, char* argv[]) { 
  highwayhash::RunTests(); 
  return 0; 
} 
#endif 
