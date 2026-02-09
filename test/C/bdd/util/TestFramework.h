/**
 * This is C test framework header.
 * 
 * Author: Chinthaka Senanayaka
 * Email: senanayw@mcmaster.ca (senanayakachinthaka@gmail.com)
 * Year: 2025
*/

/**
 * This is to setup test environment with all the preconditions before all the test runs.
 * 
 * beforeAll() always no input and no output return function. Please define all the precondition states 
 * on your test file and establish/initialize all the preconditions in this function.
 */
void beforeAll();

/**
 * This is to establish preconditions specific to your test case.
 * 
 * beforeEach() always no input and no output return function. Please define specific precondition states 
 * on your test file and establish/initialize all the preconditions in this function.
 */
void beforeEach();

/**
 * This is to establish postconditions specific to your test case.
 * 
 * afterEach() always no input and no output return function. Please define specific postcondition states 
 * on your test file and clear/clean up all the postconditions in this function.
 */
void afterEach();

/**
 * This is to clean up test environment with all the postconditions after all the test runs.
 * 
 * afterAll() always no input and no output return function. Please define all the postcondition states 
 * on your test file and celar/clean up all the postconditions in this function.
 */
void afterAll();

/**
 * This is the structure for the real test case/function to run your test code.
 * 
 * testFuncPtrDef() always no input and no output return function. Please define all the test code 
 * on your test file implementing this function.
 */
typedef void (*testFuncPtrDef)();

/**
 * Run the individual test case along with its structure.
 * 
 * Individual test case structure consists:
 *   1. Preconditions specific to the test case. This is defined using beforeEach() function.
 *   2. Test function with your real test code. This should adhere to testFuncPtrDef function definition.
 *   3. Postconditions specific to the test case. This is defined using afterEach() function.
 * 
 * Cannot omit numTestFuncs as sizeof(testFuncDefs) cannot be used as function implementation sizes can vary based on
 * each implementations and this gives onlt the size of the function defition of the signature.
 * 
 * Input:
 *   testFuncDefs - Array of test function definitions. These test definitions should adhere to "void testFunc() {...}".
 *   numTestFuncs - number of test function structures to run.
 * 
 * Output:
 */
void runTestStructure(testFuncPtrDef testFuncDefs[], int numTestFuncs) {
    for(unsigned int testCounter = 0; testCounter < numTestFuncs; testCounter++) {
        beforeEach();
        testFuncDefs[testCounter]();
        afterEach();
    }
}

/**
 * This is to run whole test suit.
 * 
 * This will 1st run the test environment setup with your preconditions.
 * Then runs the individual test cases and its struture.
 * Then will run test environment clean up with your post conditions.
 * 
 * Input:
 *   testFuncDefs - array of test function definitions. These test definitions should adhere to "void testFunc() {...}".
 *   numTestFuncs - number of test function structures to run.
 * 
 * Output:
 */
void runAllTests(testFuncPtrDef testFuncDefs[], int numTestFuncs) {
    beforeAll();
    runTestStructure(testFuncDefs, numTestFuncs);
    afterAll();
}

/**
 * This is to run single test case.
 * 
 * This will 1st run the test environment setup with your preconditions.
 * Then runs an individual test case and its struture.
 * Then will run test environment clean up with your post conditions.
 * 
 * Input:
 *   testFuncDef - a test function definition. This test definition should adhere to "void testFunc() {...}".
 * 
 * Output:
 */
void runATest(testFuncPtrDef testFuncDef) {
    testFuncPtrDef testFuncDefs[1] = {testFuncDef};
    beforeAll();
    runTestStructure(testFuncDefs, 1);
    afterAll();
}