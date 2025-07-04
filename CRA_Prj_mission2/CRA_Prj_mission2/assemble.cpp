#include "car.cpp"

#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#define CLEAR_SCREEN "\033[H\033[2J"

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

enum QuestionType
{
    Step0_CarType_Q,
    Step1_Engine_Q,
    Step2_brakeSystem_Q,
    Step3_SteeringSystem_Q,
    Step4_Run_Test,
    MAX_QUSTION_TYPE,
};

enum CarCmd
{
    CAR_CMD_GO_BACK_STEP = 0,
    CAR_CMD_RUN,
    CAR_CMD_TEST,
    MAX_CAR_CMD
};

int stack[MAX_QUSTION_TYPE];

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

void print_car_type_message()
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
    printf("어떤 차량 타입을 선택할까요?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}
void print_engine_message()
{
    printf("어떤 엔진을 탑재할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. 고장난 엔진\n");
}

void print_brake_system_message()
{
    printf("어떤 제동장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void print_steering_system_message()
{
    printf("어떤 조향장치를 선택할까요?\n");
    printf("0. 뒤로가기\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void print_Run_Test_message()
{
    printf("멋진 차량이 완성되었습니다.\n");
    printf("어떤 동작을 할까요?\n");
    printf("0. 처음 화면으로 돌아가기\n");
    printf("1. RUN\n");
    printf("2. Test\n");
}

void print_step_message_to_user(int step) {
    printf(CLEAR_SCREEN);
    switch (step) {
    case Step0_CarType_Q:
        print_car_type_message();
        break;
    case Step1_Engine_Q:
        print_engine_message();
        break;
    case Step2_brakeSystem_Q:
        print_brake_system_message();
        break;
    case Step3_SteeringSystem_Q:
        print_steering_system_message();
        break;
    case Step4_Run_Test:
        print_Run_Test_message();
        break;
    default:
        return;
    }
    printf("===============================\n");

    return;
}

#define USER_INPUT_INVALID (-1)
#define USER_INPUT_EXIT (-2)

void remove_line_feed(char* buf)
{
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}
int get_valid_answer_number(char* buf)
{
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        return USER_INPUT_INVALID;
    }

    return answer;
}

int check_answer_range_validity(int step, int answer) {
    switch (step) {
    case Step0_CarType_Q:
        if ((answer <= CAR_CMD_GO_BACK_STEP) || (answer >= MAX_CAR_TYPE)) {
            printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step1_Engine_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_ENGINE_TYPE)) {
            printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step2_brakeSystem_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_BRAKE_SYSTEM_TYPE)) {
            printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step3_SteeringSystem_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_STEERING_SYSTEM_TYPE)) {
            printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step4_Run_Test:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_CAR_CMD)) {
            printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
            return USER_INPUT_INVALID;
        }
        break;
    default:
        break;
    }

    return answer;
}

int get_user_input(int step) {
    char buf[100];
    int answer = USER_INPUT_INVALID;

    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    remove_line_feed(buf);
    if (!strcmp(buf, "exit"))
        return USER_INPUT_EXIT;

    answer = get_valid_answer_number(buf);
    if (answer == USER_INPUT_INVALID)
        return answer;

    answer = check_answer_range_validity(step, answer);

    return answer;
}

int run_user_answer(int step, int answer) {
    int next_step = step;

    switch (step) {
    case Step0_CarType_Q:
        selectCarType(answer);
        delay(800);
        next_step = Step1_Engine_Q;
        break;
    case Step1_Engine_Q:
        selectEngine(answer);
        delay(800);
        next_step = Step2_brakeSystem_Q;
        break;
    case Step2_brakeSystem_Q:
        selectbrakeSystem(answer);
        delay(800);
        next_step = Step3_SteeringSystem_Q;
        break;
    case Step3_SteeringSystem_Q:
        selectSteeringSystem(answer);
        delay(800);
        next_step = Step4_Run_Test;
        break;
    case Step4_Run_Test:
        if (answer == CAR_CMD_RUN) {
            runProducedCar();
            delay(2000);
        }
        if (answer == CAR_CMD_TEST) {
            printf("Test...\n");
            delay(1500);
            testProducedCar();
            delay(2000);
        }
        break;

    default:
        break;
    }

    return next_step;
}

int main()
{
    int step = Step0_CarType_Q;
    int answer;

    while (1)
    {
        print_step_message_to_user(step);

        answer = get_user_input(step);
        if (answer == USER_INPUT_EXIT) {
            printf("바이바이\n");
            break;
        }

        if (answer == USER_INPUT_INVALID) {
            delay(800);
            continue;
        }

        // 처음으로 돌아가기
        if (answer == CAR_CMD_GO_BACK_STEP && step == Step4_Run_Test)
        {
            step = Step0_CarType_Q;
            continue;
        }

        // 이전으로 돌아가기
        if (answer == CAR_CMD_GO_BACK_STEP && step >= 1)
        {
            step -= 1;
            continue;
        }

        step = run_user_answer(step, answer);
    }
}

void selectCarType(int answer)
{
    //String a_car[MAX_CAR_TYPE] = {"SEDAN", "SUV", "TRUCK"}
    stack[Step0_CarType_Q] = answer;
    if (answer == SEDAN)
        printf("차량 타입으로 Sedan을 선택하셨습니다.\n");
    if (answer == SUV)
        printf("차량 타입으로 SUV을 선택하셨습니다.\n");
    if (answer == TRUCK)
        printf("차량 타입으로 Truck을 선택하셨습니다.\n");
}

void selectEngine(int answer)
{
    stack[Step1_Engine_Q] = answer;
    if (answer == GM)
        printf("GM 엔진을 선택하셨습니다.\n");
    if (answer == TOYOTA)
        printf("TOYOTA 엔진을 선택하셨습니다.\n");
    if (answer == WIA)
        printf("WIA 엔진을 선택하셨습니다.\n");
}

void selectbrakeSystem(int answer)
{
    stack[Step2_brakeSystem_Q] = answer;
    if (answer == MANDO)
        printf("MANDO 제동장치를 선택하셨습니다.\n");
    if (answer == CONTINENTAL)
        printf("CONTINENTAL 제동장치를 선택하셨습니다.\n");
    if (answer == BOSCH_B)
        printf("BOSCH 제동장치를 선택하셨습니다.\n");
}

void selectSteeringSystem(int answer)
{
    stack[Step3_SteeringSystem_Q] = answer;
    if (answer == BOSCH_S)
        printf("BOSCH 조향장치를 선택하셨습니다.\n");
    if (answer == MOBIS)
        printf("MOBIS 조향장치를 선택하셨습니다.\n");
}

int isValidCheck()
{
    if (stack[Step0_CarType_Q] == SEDAN && stack[Step2_brakeSystem_Q] == CONTINENTAL)
        return false;

    if (stack[Step0_CarType_Q] == SUV && stack[Step1_Engine_Q] == TOYOTA)
        return false;

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step1_Engine_Q] == WIA)
        return false;

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step2_brakeSystem_Q] == MANDO)
        return false;

    if (stack[Step2_brakeSystem_Q] == BOSCH_B && stack[Step3_SteeringSystem_Q] != BOSCH_S)
        return false;

    return true;
}

void runProducedCar()
{
    if (isValidCheck() == false)
    {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    if (stack[Step1_Engine_Q] == 4)
    {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (stack[Step0_CarType_Q] == 1)
        printf("Car Type : Sedan\n");
    if (stack[Step0_CarType_Q] == 2)
        printf("Car Type : SUV\n");
    if (stack[Step0_CarType_Q] == 3)
        printf("Car Type : Truck\n");
    if (stack[Step1_Engine_Q] == 1)
        printf("Engine : GM\n");
    if (stack[Step1_Engine_Q] == 2)
        printf("Engine : TOYOTA\n");
    if (stack[Step1_Engine_Q] == 3)
        printf("Engine : WIA\n");
    if (stack[Step2_brakeSystem_Q] == 1)
        printf("Brake System : Mando");
    if (stack[Step2_brakeSystem_Q] == 2)
        printf("Brake System : Continental\n");
    if (stack[Step2_brakeSystem_Q] == 3)
        printf("Brake System : Bosch\n");
    if (stack[Step3_SteeringSystem_Q] == 1)
        printf("SteeringSystem : Bosch\n");
    if (stack[Step3_SteeringSystem_Q] == 2)
        printf("SteeringSystem : Mobis\n");

    printf("자동차가 동작됩니다.\n");
}

void testProducedCar()
{
    if (stack[Step0_CarType_Q] == SEDAN && stack[Step2_brakeSystem_Q] == CONTINENTAL)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Sedan에는 Continental제동장치 사용 불가\n");
        return;
    }

    if (stack[Step0_CarType_Q] == SUV && stack[Step1_Engine_Q] == TOYOTA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
        return;
    }

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step1_Engine_Q] == WIA)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 WIA엔진 사용 불가\n");
        return;
    }

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step2_brakeSystem_Q] == MANDO)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Truck에는 Mando제동장치 사용 불가\n");
        return;
    }

    if (stack[Step2_brakeSystem_Q] == BOSCH_B && stack[Step3_SteeringSystem_Q] != BOSCH_S)
    {
        printf("자동차 부품 조합 테스트 결과 : FAIL\n");
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
        return;
    }

    printf("자동차 부품 조합 테스트 결과 : PASS\n");
}

#endif