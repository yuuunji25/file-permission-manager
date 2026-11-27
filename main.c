#include <stdio.h>
#include <Windows.h>
#include <string.h>

struct User {
	char name[20];
	int read_permission;
	int write_permission;
};
struct Permission {
	int read;
	int write;
};

int main(void) {
	
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int choice;
	char new_name[20];
	char files[5][20];
	int file_count = 0;
	int user_count = 0;
	struct User users[5];
	struct Permission permissions[5][5] = { 0 };

	while (1) {
		printf("----USER ACCESS CONTROL----\n"); //초기 화면
		printf("1. 사용자 등록\n");
		printf("2. 사용자 목록\n");
		printf("3. 파일 등록\n");
		printf("4. 파일 목록\n")	;
		printf("5. 파일 권한 설정\n");
		printf("6. 파일 권한 확인\n");
		printf("7. 종료\n");

		scanf_s("%d", &choice);
		if (choice == 1) {
			if (user_count < 5) {
				printf("사용자 등록을 선택했습니다.\n");
				printf("등록할 사용자 이름: "); //사용자 등록 
				scanf_s("%19s", new_name, 20);

				int duplicate = 0; //중복 사용자 이름 확인 
				for (int i = 0; i < user_count; i++) { //등록된 사용사 수 만큼 반복
					if (strcmp(new_name, users[i].name) == 0) { //문자열 비교 함수 strcmp 사용 names[i] 기존 등록된 이름 중 하나
						duplicate = 1; //new_name 입력한 사용자 이름 임시 보관 변수
						break;
					}
				}
				if (duplicate == 1) { //중복 사용자 확인
					printf("이미 등록된 사용자입니다.\n");
				}
				else {
					strcpy_s(users[user_count].name, 20, new_name);

					users[user_count].read_permission = 0;
					users[user_count].write_permission = 0; //읽기, 쓰기 접근 권한 부여

				user_count++; //등록된 사용자 수 1증가
				printf("사용자가 등록되었습니다.\n");
				}
			}
			else {
				printf("사용자 등록 공간이 가득 찼습니다.\n"); //공간 부족
			}
		}

		else if (choice == 2) {
			printf("사용자 목록을 선택했습니다.\n"); //사용자 목록 확인

			if (user_count == 0) {
				printf("등록된 사용자가 없습니다.\n");
			}
			else {
				for (int i = 0; i < user_count; i++) {
					printf("%d. %s\n", i + 1, users[i].name);
				}
			}
		}

		else if (choice == 3) {
			if (file_count < 5) {
				char new_file[20];
				printf("등록할 파일 이름: ");
				scanf_s("%19s", new_file, 20);

				int duplicate = 0;

				for (int i = 0; i < file_count; i++) {
					if (strcmp(new_file, files[i]) == 0) {
						duplicate = 1;
						break;
					}
				}
				if (duplicate == 1) {
					printf("이미 등록된 파일입니다.\n");
				}
				else {
					strcpy_s(files[file_count], 20, new_file);
					file_count++;
					printf("파일이 등록되었습니다.\n");
				}
			}
			else {
				printf("파일 등록 공간이 가득 찼습니다.\n");
			}
		}

		else if (choice == 4) {
			printf("파일 목록을 선택했습니다.\n");

			if (file_count == 0) {
				printf("등록된 파일이 없습니다\n");
			}
			else {
				for (int i = 0; i < file_count; i++) {
					printf("%d, %s\n", i + 1, files[i]);
				}
			}
		}
		else if (choice == 5) {
			int user_num, file_num;
			int permission_choice;
			int permission_value;

			if (user_count == 0 || file_count == 0) {
				printf("등록된 사용자와 파일이 모두 필요합니다.\n");
				continue;
			}
			printf("등록된 사용자 목록: \n"); //등록된 사용자 목록 확인
			for (int i = 0; i < user_count; i++) {
				printf("%d. %s\n", i + 1, users[i].name);
			}
			printf("권한을 부여할 사용자 번호: ");
			scanf_s("%d", &user_num);

			if (user_num <1 || user_num>user_count) { //사용자 번호 유효성 확인
				printf("잘못된 사용자 번호입니다.\n");
				continue;
			}
			printf("\n등록된 파일 목록: \n"); //등록된 파일 목록 확인
			for (int i = 0; i < file_count; i++) {
				printf("%d. %s\n", i + 1, files[i]);
			}
			printf("권한을 설정할 파일 번호: \n");
			scanf_s("%d", &file_num);

			if (file_num<1 || file_num>file_count) {
				printf("잘못된 파일 번호입니다. \n");
				continue;
			}
			printf("\n1. 읽기 권한\n");
			printf("2. 쓰기 권한\n");
			printf("선택: ");
			scanf_s("%d", &permission_choice);

			if (permission_choice != 1 && permission_choice != 2) {
				printf("잘못된 선택입니다.\n");
				continue;
			}

			printf("권한을 허용할까요? (1:허용, 0:거부): ");
			scanf_s("%d", &permission_value);

			if (permission_value != 0 && permission_value != 1) {
				printf("잘못된 권한 값입니다.\n");
				continue;
			}

			if (permission_choice == 1) { //읽기 권한 설정
				permissions[user_num - 1][file_num - 1].read = permission_value;
			}
			else { //쓰기 권한 설정
				permissions[user_num - 1][file_num - 1].write = permission_value;
			}
			if (permission_value == 1) {
				printf("권한이 부여되었습니다. \n");
			}
			else {
				printf("권한 부여가 거부되었습니다. \n");
			}
		}
		else if (choice==6) {
			int user_num, file_num;
			int access_choice;

			if (user_count == 0 || file_count == 0) {
				printf("등록된 사용자와 파일이 모두 필요합니다.\n");
				continue;
			}
			printf("등록된 사용자 목록: \n");
			for (int i = 0; i < user_count; i++) {
				printf("%d. %s\n", i + 1, users[i].name);
			}
			printf("권한을 확인할 사용자 번호: ");
			scanf_s("%d", &user_num);

			if (user_num<1 || user_num>user_count) { //사용자 번호 유효성 확인 
				printf("잘못된 사용자 번호입니다.\n");
				continue;
			}
			printf("\n선택한 사용자: %s\n", users[user_num-1].name);
			
			printf("\n권한을 확인할 파일 목록: \n"); //등록된 파일 목록 확인
			for (int i = 0; i < file_count; i++) {
				printf("%d. %s\n", i + 1, files[i]);
			}

			printf("권한을 확인할 파일 번호: ");
			scanf_s("%d", &file_num);

			if (file_num<1 || file_num>file_count) { //파일 번호 유효성 확인
				printf("잘못된 파일 번호입니다.\n");
				continue;
			}

			printf("\n선택한 파일: %s\n", files[file_num-1]);
			printf("----FILE PERMISSION----\n");

			if (permissions[user_num - 1][file_num - 1].read == 1) {
				printf("읽기 권한 : 허용\n");
			}
			else {
				printf("파일 권한 : 거부\n");
			}
			if (permissions[user_num - 1][file_num - 1].write == 1) {
				printf("쓰기 권한 : 허용\n");
			}
			else {
				printf("쓰기 권한 : 거부\n");
			}
		}
		else if (choice == 7) {
			printf("프로그램을 종료합니다.\n");
			break;
		}
		else {
			printf("잘못된 선택입니다.\n");
		}
	}
	return 0;
}
