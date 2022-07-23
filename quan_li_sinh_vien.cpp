#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

const int MAX = 100;

struct SinhVien
{
	std::string name;
	int age;
	float point;
};

// Lay thong tin sinh vien tu file.
int load_sv(std::string filename, SinhVien* sv) {
	int i = 0;
	std::ifstream input;
	std::string line;
	input.open(filename);
	
	while (getline(input, line)) {
		std::string delimiter = ";";
		int pos_of_delimiter = line.find(delimiter);
		if (pos_of_delimiter != std::string::npos) {
			(sv + i)->name = line.substr(0, pos_of_delimiter);
			line = line.substr(pos_of_delimiter + 1, line.length() - 1);
			pos_of_delimiter = line.find(delimiter);
			(sv + i)->age = stoi(line.substr(0, pos_of_delimiter));
			line = line.substr(pos_of_delimiter + 1, line.length() - 1);
			pos_of_delimiter = line.find(delimiter);
			(sv + i)->point = stof(line.substr(0, pos_of_delimiter));
		}
		i++;
	}

	input.close();
	return i;
}

// In thong tin sinh vien.
void print_sv(SinhVien* sv, int n) {
	const int size_stt = 6;
	const int size_ten = 25;
	const int size_tuoi = 9;
	const int size_diem = 9;

	std::cout << "\t\t+-----+------------------------+--------+--------+" << "\n";
	std::cout << std::left;
	std::cout << "\t\t" << std::setw(size_stt) << "| STT" << std::setw(size_ten) << "| Ho va ten" << std::setw(size_tuoi) << "| Tuoi" << std::setw(size_diem) << "| Diem" << "|" << "\n";
	std::cout << "\t\t+-----+------------------------+--------+--------+" << "\n";

	for (int i = 0; i < n; i++) {
		std::cout << "\t\t|  " << std::setw(size_stt - 3) << i + 1 << "| " << std::setw(size_ten - 2) << (sv + i)->name << "|  " << std::setw(size_tuoi - 3) << (sv + i)->age << "|  " << std::setw(size_diem - 3) << (sv + i)->point << "|" << "\n";
	}
	std::cout << "\t\t+-----+------------------------+--------+--------+\n" << "\n";

}

// Them sinh vien moi.
void add_sv(SinhVien* sv, int& n) {
	const int size_input = 12;


	std::cout << "\n\t(!) Dien thong tin sinh vien: " << "\n\n";
	std::cout << std::left;
	std::cout << std::setw(size_input) << "" << "(?) Nhap ten sinh vien: ";
	std::cin.ignore();
	getline(std::cin, (sv + n)->name);
	std::cout << std::setw(size_input) << "" << "(?) Nhap tuoi sinh vien: ";
	std::cin >> (sv + n)->age;
	std::cout << std::setw(size_input) << "" << "(?) Nhap diem sinh vien: ";
	std::cin >> (sv + n)->point;
	std::cout << std::setw(size_input) << "" << "(!) Da them sinh vien. " << "\n\n";
	n++;
}

// Sua thong tin sinh vien.
void fix_sv(SinhVien* sv, int n, int pos_sv) {
	for (int i = 0; i < n; i++) {
		if (i == pos_sv - 1) {
			int info_sv;
			std::cout << "\t\t=====================" << "\n";
			std::cout << "\t\t(1) Ten sinh vien." << "\n";
			std::cout << "\t\t(2) Tuoi sinh vien." << "\n";
			std::cout << "\t\t(3) Diem sinh vien." << "\n";
			std::cout << "\t\t=====================" << "\n";

			std::cout << "\t(?) Ban muon sua thong tin nao: ";
			std::cin >> info_sv;
			switch (info_sv) {
			case 1:
				std::cout << "\t\t  (*) Ten moi cua sinh vien: ";
				std::cin.ignore();
				getline(std::cin, (sv + i)->name);
				break;
			case 2:
				std::cout << "\t\t  (*) Tuoi moi cua sinh vien: ";
				std::cin >> (sv + i)->age;
				break;
			case 3:
				std::cout << "\t\t  (*) Diem moi cua sinh vien: ";
				std::wcin >> (sv + i)->point;
				break;
			default:
				std::wcout << "\t\t (!) Chon sai" << "\n";
				break;
			}
		}
	}
}

// Xoa sinh vien.
void remove_sv(SinhVien* sv, int& n, int pos_sv) {
	for (int i = pos_sv - 1; i < n; i++) {
		(sv + i)->name = (sv + i + 1)->name;
		(sv + i)->age = (sv + i + 1)->age;
		(sv + i)->point = (sv + i + 1)->point;
	}
	n--;
}

// Tim kiem sinh vien.
std::string up_to_low_case(std::string name) {
	for (int i = 0; i < name.length(); i++) {
		for (char c = 'A'; c < 'Z'; c++) {
			if (name[i] == c) {
				name[i] += 32;
			}
		}
	}
	return name;
}

void search_sv(SinhVien* sv, int n) {
	std::string key_word;
	int count = 0;
	SinhVien* sv_search = new SinhVien[MAX];
	std::cout << "\t(?) Nhap ten sinh vien can tim: ";
	std::cin.ignore();
	getline(std::cin, key_word);
	std::string key_word_low = up_to_low_case(key_word);
	for (int i = 0; i < n; i++) {
		bool test_char = false;
		for (int j = 0; j < (sv+i)->name.length(); j++) {
			if (up_to_low_case((sv + i)->name)[j] == key_word_low[0]) {
				std::string line = up_to_low_case((sv + i)->name).substr(j, key_word.length());
				if (line == key_word_low) {
					test_char = true;
					break;
				}
			}
		}
		if (test_char) {
			(sv_search + count)->name = (sv + i)->name;
			(sv_search + count)->age = (sv + i)->age;
			(sv_search + count)->point = (sv + i)->point;
			count++;
		}
	}
	print_sv(sv_search, count);
}

// Sap xep sinh vien
//----------------------------------------------------
	// Sap xep theo ten ABC
std::string get_name_sv(std::string name) {
	std::string only_name;
	bool check_trang = false;
	for (int i = name.length() - 1; i >= 0; i--) {
		if (name[i] == ' ') {
			check_trang = true;
			only_name = name.substr(i + 1, name.length() - i);
			break;
		}
	}
	if (!check_trang) {
		only_name = name;
	}
	return only_name;
}

void sort_sv_name(SinhVien* sv, int n) {
	SinhVien* sv_name = new SinhVien[MAX];
	for (int i = 0; i < n; i++) {
		(sv_name + i)->name = (sv + i)->name;
		(sv_name + i)->age = (sv + i)->age;
		(sv_name + i)->point = (sv + i)->point;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {			
			for (int l = 0; l < (get_name_sv(up_to_low_case((sv_name + i)->name)).length() >= get_name_sv(up_to_low_case((sv_name + j)->name)).length()) ? get_name_sv(up_to_low_case((sv_name + j)->name)).length() : get_name_sv(up_to_low_case((sv_name + i)->name)).length(); l++) {
				if (get_name_sv(up_to_low_case((sv_name + i)->name))[l] > get_name_sv(up_to_low_case((sv_name + j)->name))[l]) {					
					SinhVien temp = sv_name[i];
					sv_name[i] = sv_name[j];
					sv_name[j] = temp;
					break;
				}
				else if (get_name_sv(up_to_low_case((sv_name + i)->name))[l] < get_name_sv(up_to_low_case((sv_name + j)->name))[l]) {
					break;
				}
				else if (get_name_sv(up_to_low_case((sv_name + i)->name)) == get_name_sv(up_to_low_case((sv_name + j)->name))) {
					break;
				}
			}
		}
	}
	print_sv(sv_name, n);
}
	// Sap xep theo tuoi tang dan
void sort_sv_age(SinhVien* sv, int n) {
	SinhVien* sv_age = new SinhVien[MAX];
	for (int i = 0; i < n; i++) {
		(sv_age + i)->name = (sv + i)->name;
		(sv_age + i)->age = (sv + i)->age;
		(sv_age + i)->point = (sv + i)->point;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((sv_age + i)->age > (sv_age + j)->age) {
				SinhVien temp = sv_age[i];
				sv_age[i] = sv_age[j];
				sv_age[j] = temp;
			}			
		}
	}
	print_sv(sv_age, n);
}
	// Sap xep theo diem tang dan
void sort_sv_point(SinhVien* sv, int n) {
	SinhVien* sv_point = new SinhVien[MAX];
	for (int i = 0; i < n; i++) {
		(sv_point + i)->name = (sv + i)->name;
		(sv_point + i)->age = (sv + i)->age;
		(sv_point + i)->point = (sv + i)->point;
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if ((sv_point + i)->point > (sv_point + j)->point) {
				SinhVien temp = sv_point[i];
				sv_point[i] = sv_point[j];
				sv_point[j] = temp;
			}
		}
	}
	print_sv(sv_point, n);
}
//----------------------------------------------------
void sort_sv(SinhVien* sv, int n) {
	int key;
	std::cout << "\n\t\t(1) Sap xep theo ten ABC." << "\n";
	std::cout << "\t\t(2) Sap xep theo tuoi tang dan." << "\n";
	std::cout << "\t\t(3) Sap xep theo diem tang dan." << "\n\n";
	std::cout << "\t(?) Ban muon lam gi? "; std::cin >> key;
	switch (key) {
	case 1:
		sort_sv_name(sv, n);
		break;
	case 2:
		sort_sv_age(sv, n);
		break;
	case 3:
		sort_sv_point(sv, n);
		break;
	default:
		std::wcout << "\t\t (!) Chon sai" << "\n";
		break;
	}
}

// Thong ke
float point_tb(SinhVien* sv, int n) {
	float sum_point = 0;
	for (int i = 0; i < n; i++) {
		sum_point += (sv + i)->point;
	}
	return sum_point / n;
}

void rank_sv(SinhVien* sv, int n) {
	int sv_gioi = 0, sv_tb = 0, sv_yeu = 0;
	for (int i = 0; i < n; i++) {
		if ((sv + i)->point >= 8) {
			sv_gioi++;
		}
		else if ((sv + i)->point >= 5) {
			sv_tb++;
		}
		else {
			sv_yeu++;
		}
	}
	std::cout << "\t\t(!) Ti le hoc sinh gioi la: " << (float)sv_gioi * 100 / n << "%\n";
	std::cout << "\t\t(!) Ti le hoc sinh trung binh la: " << (float)sv_tb * 100 / n << "%\n";
	std::cout << "\t\t(!) Ti le hoc sinh yeu la: " << (float)sv_yeu * 100 / n << "%\n";
}

void best_sv(SinhVien* sv, int n) {
	float point_max = (sv + 0)->point;
	for (int i = 0; i < n; i++) {
		point_max = ((sv + i)->point > point_max) ? (sv + i)->point : point_max;
	}
	for (int i = 0; i < n; i++) {
		if ((sv + i)->point == point_max) {
			std::cout << "\t\t\t+ " << (sv + i)->name << "\n";
		}
	}
}

void statistic_sv(SinhVien* sv, int n) {
	std::cout << "\t\t(!) Diem trung binh sinh vien la: " << point_tb(sv, n) << "\n";
	rank_sv(sv, n);
	std::cout << "\t\t(!) Sinh vien co diem cao nhat la: " << "\n";
	best_sv(sv, n);
}

// Luu thong tin
void save_sv(std::string filename, SinhVien* sv, int n) {
	std::ofstream output;
	output.open(filename);
	
	for (int i = 0; i < n; i++) {
		output << (sv + i)->name << ";" << (sv + i)->age << ";" << (sv + i)->point << "\n";
	}

	output.close();
}

// Ham main
int main() {
	int key, stt_sv;
	const std::string filename = "QLSV.txt";
	SinhVien* sv = new SinhVien[MAX];
	int num_of_sv = load_sv(filename, sv);

	const int size_tb = 31;

	while (true) {
		std::cout << std::left;
		std::cout << "+=================MENU=================+" << "\n";
		std::cout << std::setw(39) << "| (1). In thong tin sinh vien." << "|" << "\n";
		std::cout << std::setw(39) << "| (2). Them sinh vien." << "|" << "\n";
		std::cout << std::setw(39) << "| (3). Sua sinh vien." << "|" << "\n";
		std::cout << std::setw(39) << "| (4). Xoa sinh vien." << "|" << "\n";
		std::cout << std::setw(39) << "| (5). Tim kiem." << "|" << "\n";
		std::cout << std::setw(39) << "| (6). Xap xep." << "|" << "\n";
		std::cout << std::setw(39) << "| (7). Thong ke." << "|" << "\n";
		std::cout << std::setw(39) << "| (8). Luu thong tin." << "|" << "\n";
		std::cout << std::setw(39) << "| (9). Thoat chuong trinh." << "|" << "\n";
		std::cout << std::setw(39) << "+======================================+" << "\n";
		std::cout << "(?). Moi ban lua chon: "; std::cin >> key;
		switch (key) {
		case 1:
			std::cout << "\n" << std::setw(size_tb) << "" << "THONG TIN SINH VIEN" << "\n";
			print_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 2:
			add_sv(sv, num_of_sv);
			std::cout << "\n" << std::setw(size_tb) << "" << "DA THEM THANH CONG" << "\n";
			print_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 3:
			std::cout << "\n" << std::setw(size_tb) << "" << "SUA THONG TIN SINH VIEN" << "\n";
			print_sv(sv, num_of_sv);
			do {
				std::cout << "\t(?) Nhap STT sinh vien: "; std::cin >> stt_sv;
			} while (stt_sv <= 0 || stt_sv > num_of_sv);
			fix_sv(sv, num_of_sv, stt_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 4:
			std::cout << "\n" << std::setw(size_tb) << "" << "\tXOA SINH VIEN" << "\n";
			print_sv(sv, num_of_sv);
			do {
				std::cout << "\t(?) Nhap STT sinh vien ban muon xoa: "; std::cin >> stt_sv;
			} while (stt_sv <= 0 || stt_sv > num_of_sv);
			remove_sv(sv, num_of_sv, stt_sv);
			std::cout << "\n" << std::setw(size_tb) << "" << "DA XOA THANH CONG" << "\n";
			print_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 5:
			std::cout << "\n" << std::setw(size_tb) << "" << "TIM KIEM SINH VIEN" << "\n";
			search_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 6:
			std::cout << "\n" << std::setw(size_tb) << "" << "SAP XEP SINH VIEN" << "\n";
			sort_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 7:
			std::cout << "\n" << std::setw(size_tb) << "" << "THONG KE SINH VIEN" << "\n";
			statistic_sv(sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 8:
			std::cout << "\n" << std::setw(size_tb) << "" << "LUU THONG TIN SINH VIEN" << "\n";
			std::cout << "\t(!) Dang luu thong tin: ";
			for (int i = 0; i < 50; i++) {
				std::cout << "|";
				Sleep(100);
			}
			std::cout << "\n\t(!) Da luu thong tin xong." << "\n";
			save_sv(filename, sv, num_of_sv);
			std::cout << "\t(!). Nhap phim bat ky de tiep tuc..." << "\n";
			_getch();
			system("cls");
			break;
		case 9:
			std::cout << "\n(!). Cam on ban da su dung chuong trinh. (^^)\n";
			return 0;
		}
	}

	delete []sv;
	return 0;
}