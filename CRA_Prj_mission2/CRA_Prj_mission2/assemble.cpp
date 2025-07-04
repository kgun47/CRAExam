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
    printf("� ���� Ÿ���� �����ұ��?\n");
    printf("1. Sedan\n");
    printf("2. SUV\n");
    printf("3. Truck\n");
}
void print_engine_message()
{
    printf("� ������ ž���ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. GM\n");
    printf("2. TOYOTA\n");
    printf("3. WIA\n");
    printf("4. ���峭 ����\n");
}

void print_brake_system_message()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. MANDO\n");
    printf("2. CONTINENTAL\n");
    printf("3. BOSCH\n");
}

void print_steering_system_message()
{
    printf("� ������ġ�� �����ұ��?\n");
    printf("0. �ڷΰ���\n");
    printf("1. BOSCH\n");
    printf("2. MOBIS\n");
}

void print_Run_Test_message()
{
    printf("���� ������ �ϼ��Ǿ����ϴ�.\n");
    printf("� ������ �ұ��?\n");
    printf("0. ó�� ȭ������ ���ư���\n");
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
    int answer = strtol(buf, &checkNumber, 10); // ���ڿ��� 10������ ��ȯ

    // �Է¹��� ���ڰ� ���ڰ� �ƴ϶��
    if (*checkNumber != '\0')
    {
        printf("ERROR :: ���ڸ� �Է� ����\n");
        return USER_INPUT_INVALID;
    }

    return answer;
}

int check_answer_range_validity(int step, int answer) {
    switch (step) {
    case Step0_CarType_Q:
        if ((answer <= CAR_CMD_GO_BACK_STEP) || (answer >= MAX_CAR_TYPE)) {
            printf("ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step1_Engine_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_ENGINE_TYPE)) {
            printf("ERROR :: ������ 1 ~ 4 ������ ���� ����\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step2_brakeSystem_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_BRAKE_SYSTEM_TYPE)) {
            printf("ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step3_SteeringSystem_Q:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_STEERING_SYSTEM_TYPE)) {
            printf("ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n");
            return USER_INPUT_INVALID;
        }
        break;
    case Step4_Run_Test:
        if ((answer < CAR_CMD_GO_BACK_STEP) || (answer >= MAX_CAR_CMD)) {
            printf("ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n");
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
            printf("���̹���\n");
            break;
        }

        if (answer == USER_INPUT_INVALID) {
            delay(800);
            continue;
        }

        // ó������ ���ư���
        if (answer == CAR_CMD_GO_BACK_STEP && step == Step4_Run_Test)
        {
            step = Step0_CarType_Q;
            continue;
        }

        // �������� ���ư���
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
        printf("���� Ÿ������ Sedan�� �����ϼ̽��ϴ�.\n");
    if (answer == SUV)
        printf("���� Ÿ������ SUV�� �����ϼ̽��ϴ�.\n");
    if (answer == TRUCK)
        printf("���� Ÿ������ Truck�� �����ϼ̽��ϴ�.\n");
}

void selectEngine(int answer)
{
    stack[Step1_Engine_Q] = answer;
    if (answer == GM)
        printf("GM ������ �����ϼ̽��ϴ�.\n");
    if (answer == TOYOTA)
        printf("TOYOTA ������ �����ϼ̽��ϴ�.\n");
    if (answer == WIA)
        printf("WIA ������ �����ϼ̽��ϴ�.\n");
}

void selectbrakeSystem(int answer)
{
    stack[Step2_brakeSystem_Q] = answer;
    if (answer == MANDO)
        printf("MANDO ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == CONTINENTAL)
        printf("CONTINENTAL ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == BOSCH_B)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
}

void selectSteeringSystem(int answer)
{
    stack[Step3_SteeringSystem_Q] = answer;
    if (answer == BOSCH_S)
        printf("BOSCH ������ġ�� �����ϼ̽��ϴ�.\n");
    if (answer == MOBIS)
        printf("MOBIS ������ġ�� �����ϼ̽��ϴ�.\n");
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
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    if (stack[Step1_Engine_Q] == 4)
    {
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
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

    printf("�ڵ����� ���۵˴ϴ�.\n");
}

void testProducedCar()
{
    if (stack[Step0_CarType_Q] == SEDAN && stack[Step2_brakeSystem_Q] == CONTINENTAL)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Sedan���� Continental������ġ ��� �Ұ�\n");
        return;
    }

    if (stack[Step0_CarType_Q] == SUV && stack[Step1_Engine_Q] == TOYOTA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("SUV���� TOYOTA���� ��� �Ұ�\n");
        return;
    }

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step1_Engine_Q] == WIA)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� WIA���� ��� �Ұ�\n");
        return;
    }

    if (stack[Step0_CarType_Q] == TRUCK && stack[Step2_brakeSystem_Q] == MANDO)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Truck���� Mando������ġ ��� �Ұ�\n");
        return;
    }

    if (stack[Step2_brakeSystem_Q] == BOSCH_B && stack[Step3_SteeringSystem_Q] != BOSCH_S)
    {
        printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n");
        printf("Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n");
        return;
    }

    printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n");
}

#endif