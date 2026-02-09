/**
 * Utility C code for SIMD coding.
 * 
 * Author: Chinthaka Senanayaka
 * Year: 2025
*/
// Macro enums to define processor platform
#define ENV_INTEL 1
#define ENV_WASM 2
#define ENV_ARM 3
#define ENV_RISCV 4

// Macro to specify which SIMD platform to use.
#if defined(ENV) && (ENV == ENV_INTEL || ENV == ENV_WASM)
    #include <immintrin.h>
#elif defined(ENV) && ENV == ENV_ARM
    #include <arm_neon.h>
#elif defined(ENV) && ENV == ENV_RISCV
    #include <riscv_vector.h>
#else
    #include <immintrin.h>
#endif

#ifndef __SimdUtil_C__
#define __SimdUtil_C__

// vectype is generic type to hold SIMD vector type. Always group size * 8bits char used to occupy 128 SIMD registers.
// reversedVectorData is to define SIMD registers are indexed forward or reversed based on the processor platform.
#if defined(ENV) && (ENV == ENV_INTEL || ENV == ENV_WASM)
typedef __m128i vectype;
short reversedVectorData = 1;
#elif defined(ENV) && ENV == ENV_ARM
typedef int8x16_t vectype;
short reversedVectorData = 0;
#elif defined(ENV) && ENV == ENV_RISCV
typedef vint8m1_t vectype;
short reversedVectorData = 0;
#else
typedef __m128i vectype;
short reversedVectorData = 1;
#endif

/**
 * This broadcasts given single 8 bit char value to group size (16 slots) in 128 bit SIMD register.
 * 
 * Input:
 *  val - 8 bit char value to broadcast.
 * 
 * Output: 
 *  vectype - 128 bit SIMD array of values based on the processor platform.
 */
vectype broadcastValToVector(char val) {
    vectype charGrpVector;

#if defined(ENV) && (ENV == ENV_INTEL || ENV == ENV_WASM)
    charGrpVector = _mm_set1_epi8(val);
#elif defined(ENV) && ENV == ENV_ARM
    charGrpVector = vmovq_n_s8(val);
#elif defined(ENV) && ENV == ENV_RISCV
    // vl stands for max number of elements can be stored in the SIMD register vector.
    size_t vl = __riscv_vsetvlmax_e8m1();
    vectype char1Vector = __riscv_vle8_v_i8m1(&val, vl);
    charGrpVector = __riscv_vrgather_vx_i8m1(char1Vector, 0, vl);
#else
    charGrpVector = _mm_set1_epi8(val);
#endif

    return charGrpVector;
}

/**
 * Getter function to load 128 bit SIMD register vector with given 8 bit array.
 * 
 * Input:
 *  arrayPtrGrp - 8 bit signed char array pointer.
 * 
 * Output: 
 *  vectype - 128 bit SIMD array of values based on the processor platform.
 */
vectype getMetaVectorGrp(signed char *arrayPtrGrp) {
    vectype charGrpVector;

#if defined(ENV) && (ENV == ENV_INTEL || ENV == ENV_WASM)
    charGrpVector = _mm_set_epi8(*(arrayPtrGrp + 0), *(arrayPtrGrp + 1), *(arrayPtrGrp + 2), 
            *(arrayPtrGrp + 3), *(arrayPtrGrp + 4), *(arrayPtrGrp + 5), *(arrayPtrGrp + 6), 
            *(arrayPtrGrp + 7), *(arrayPtrGrp + 8), *(arrayPtrGrp + 9), *(arrayPtrGrp + 10), 
            *(arrayPtrGrp + 11), *(arrayPtrGrp + 12), *(arrayPtrGrp + 13), 
            *(arrayPtrGrp + 14), *(arrayPtrGrp + 15));
#elif defined(ENV) && ENV == ENV_ARM
    charGrpVector = vld1q_s8(arrayPtrGrp);
#elif defined(ENV) && ENV == ENV_RISCV
    // vl stands for max number of elements can be stored in the SIMD register vector.
    size_t vl = __riscv_vsetvlmax_e8m1();
    charGrpVector = __riscv_vle8_v_i8m1(arrayPtrGrp, vl);
#else
    charGrpVector = _mm_set_epi8(*(arrayPtrGrp + 0), *(arrayPtrGrp + 1), *(arrayPtrGrp + 2), 
            *(arrayPtrGrp + 3), *(arrayPtrGrp + 4), *(arrayPtrGrp + 5), *(arrayPtrGrp + 6), 
            *(arrayPtrGrp + 7), *(arrayPtrGrp + 8), *(arrayPtrGrp + 9), *(arrayPtrGrp + 10), 
            *(arrayPtrGrp + 11), *(arrayPtrGrp + 12), *(arrayPtrGrp + 13), 
            *(arrayPtrGrp + 14), *(arrayPtrGrp + 15));
#endif
    
    return charGrpVector;
}

/**
 * Internal: To get array of masked booleans based on the operation previously did on the SIMD vector.
 * 
 * getMaskMatchVals() function signature is SimdUtil internal function which changes its signature 
 * based on the platform requirements and being called by getMatchMaskGrp() function in the same SimdUtil.
 * 
 * Input:
 *  input - input array of masked values.
 *  groupSize - group size. A.K.A number of slots in the SIMD vector.
 *  maskedGrpBools - array of booleans resulting from the previous operations performed on the SIMD vector register.
 * 
 * Output: 
 */
#if ENV == ENV_INTEL || ENV == ENV_WASM
void getMaskMatchVals(int input, int groupSize, int maskedGrpBools[]) {
    for(int laneNum = 0; laneNum < groupSize; ++laneNum, input >>= 1)
        maskedGrpBools[laneNum] = input & 1;
}
#elif ENV == ENV_ARM
// Retrieve input integer's maskedGrpBools into an array of maskedGrpBools
void getMaskMatchVals(vectype input, int groupSize, int maskedGrpBools[]) {
    int8_t laneVals[groupSize];
    vst1q_s8(laneVals, input);

    for(int laneNum = 0; laneNum < groupSize; ++laneNum) {
        char matchVal = (char) laneVals[laneNum];
        maskedGrpBools[laneNum] = matchVal & 1;
    }
}
#elif ENV == ENV_RISCV
void getMaskMatchVals(signed char input[], int groupSize, signed int maskedGrpBools[]) {

    for(int laneNum = 0; laneNum < groupSize; ++laneNum) {
        signed char matchMaskBit = input[laneNum];
        maskedGrpBools[laneNum] = matchMaskBit;
    }
}
#else
void getMaskMatchVals(int input, int groupSize, int maskedGrpBools[]) {
    for(int laneNum = 0; laneNum < groupSize; ++laneNum, input >>= 1)
        maskedGrpBools[laneNum] = input & 1;
}
#endif

/**
 * Getter for matching 2 SIMD vector registers and mask the matching values in to booleans (1s & 0s).
 * 
 * Input:
 *  charGrpComparators - 16 * 8 char SIMD vector as the comparator.
 *  charGrpVals - 16 * 8 char SIMD vector with values from meta data array of the hash table.
 *  groupSize - group size. A.K.A number of slots in the SIMD vector.
 *  maskedGrpBools - array of booleans resulting from the previous operations performed on the SIMD vector register.
 * 
 * Output: 
 */
void getMatchMaskGrp(vectype charGrpComparators, vectype charGrpVals, int groupSize, signed int maskedGrpBools[]) {

#if defined(ENV) && (ENV == ENV_INTEL || ENV == ENV_WASM)
    int maskMatchVal = _mm_movemask_epi8(_mm_cmpeq_epi8(charGrpComparators, charGrpVals));
    getMaskMatchVals(maskMatchVal, groupSize, maskedGrpBools);
#elif defined(ENV) && ENV == ENV_ARM
    // move mask is not directy supported on ARM-Neon
    vectype matchVals = vreinterpretq_s8_u8(vceqq_s8(charGrpComparators, charGrpVals));
    getMaskMatchVals(matchVals, groupSize, maskedGrpBools);
#elif defined(ENV) && ENV == ENV_RISCV
    // vl stands for max number of elements can be stored in the SIMD register vector.
    size_t vl = __riscv_vsetvlmax_e8m1();

    signed char boolInt1[groupSize];
    for(int laneNum = 0; laneNum < groupSize; ++laneNum) {
        boolInt1[laneNum] = 1;
    }

    // There is a better way with __riscv_vmseq_vx_i8m1_b8() vx than vv,
    // but kept vv as to keep the code same like other processor code.
    // Moreover, can't switch charGrpVals and charGrpComparators on below call.
    vbool8_t trueMatchMask = __riscv_vmseq_vv_i8m1_b8(charGrpVals, charGrpComparators, vl);
    vectype maskMatch = __riscv_vle8_v_i8m1_m(trueMatchMask, boolInt1, vl);

    signed char maskMatchVal[groupSize];
    signed char *maskMatchValPtr = maskMatchVal;
    __riscv_vse8_v_i8m1(maskMatchValPtr, maskMatch, vl);

    getMaskMatchVals(maskMatchVal, groupSize, maskedGrpBools);
#else
    int maskMatchVal = _mm_movemask_epi8(_mm_cmpeq_epi8(charGrpComparators, charGrpVals));
    getMaskMatchVals(maskMatchVal, groupSize, maskedGrpBools);
#endif

}

#endif