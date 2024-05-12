#include <iostream>
#include <Windows.h>

class smart_array {
private:
	int* data;
	int size;
	int capacity;

public:

	smart_array(int start_capacity) : size(0), capacity(start_capacity) {
		if (start_capacity <= 0)
			throw std::invalid_argument("Изначальная вместимость должна быть положительной");
		data = new int[capacity];
	}

	smart_array& operator = (const smart_array& other) {
		if (this != &other) {
			delete[] data;

			size = other.size;
			capacity = other.capacity;
			data = new int[capacity];
			for (int i = 0; i < size; ++i) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	~smart_array() {
		delete[] data;
	}

	void add_element(int value) {
		if (size >= capacity) {
			capacity *= 2;
			int* new_data = new int[capacity];
			for (int i = 0; i < size; ++i) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
		}
		data[size++] = value;
	}

	int get_element(int index) const {
		if (index < 0 || index >= size)
			throw std::out_of_range("Индекс вне дипапазона");
		return data[index];
	}
};

int main(int argc, const char* argv[]) {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	try {
		smart_array arr(3);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);

		smart_array new_arr(2);
		new_arr.add_element(44);
		new_arr.add_element(34);

		arr = new_arr;

		std::cout << arr.get_element(0) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}