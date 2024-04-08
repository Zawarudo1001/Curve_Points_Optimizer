#include "FileParser.h"


int File::openfile(const char* name, const char* mode) {
	errno_t err = fopen_s(&mainfile, name, mode);
	if (err != NULL) {
		fopen_s(&mainfile, name, "w+");
	}
	fopenerror = 0;
	fclose(mainfile);
	fopen_s(&mainfile, name, mode);
	fsize = getfilesize(mainfile);
	return fopenerror;
}

ulong File::getfilesize(FILE* file) {
	fseek(file, 0, SEEK_END);
	ulong t = ftell(mainfile);
	fseek(file, 0, SEEK_SET);
	return t;
}

ulong File::parse_file(ulong start, const char* pattern, int size, bool last) {
	char buf[16];
	memset(buf, 0, 16);
	fsize = getfilesize(mainfile);
	for (ulong i = 0; i < fsize; i++) {
		fseek(mainfile, i + start, SEEK_SET);
		fread(&buf, size, 1, mainfile);
		if (memcmp(pattern, buf, size) == 0) { return i + start + (last? size : 0); }
	}
	return PARSE_ERR;
}


void File::parse_flt_data(vector<vector<Point2d>> &points, map<Point2d, uint8_t> &Point_count) {

	map<Point2d, uint8_t>::iterator it;

	char* buff;

	fseek(mainfile, 0, SEEK_SET);
	ulong start = 0;
	ulong temp_1 = 0;
	ulong temp_2 = 0;

	while(true) {
		temp_1 = parse_file(start, "<LineGeometry>", 14, LAST);			//индекс конца открывающего тега
		temp_2 = parse_file(start, "</LineGeometry>", 15, FIRST);		//индекс начала закрывающего тега
			
		vector<Point2d> p;

		if (temp_1 == PARSE_ERR or temp_2 == PARSE_ERR or temp_1 >= temp_2)
			return;		//если не удалось парсить хотя бы один из тегов, завершаем выполнение

		fseek(mainfile, temp_1, SEEK_SET);

		int b_size = temp_2 - temp_1 - 1;
		buff = new char[b_size + 1];
		memset(buff, 0, b_size + 1);

		fread(buff, b_size, 1, mainfile);

		char *end;
		char* temp = buff;

		for (float f = strtof(temp, &end); temp != end; f = strtof(temp, &end))
		{
			temp = end;
			float q = strtof(temp, &end);
			temp = end;

			if (errno == ERANGE) {
				printf("range error, got ");
				errno = 0;
			}
			Point2d s{ f, q };
			p.push_back(s);		//сюда сохраняем полученные в процесса парсинга float-значения
										// теперь нужно поместить значение f в unordered_map, предварительно проверив существование ключа
			it = Point_count.find(s);
			if (it != Point_count.end()) {
				it->second += 1;
			}
			else Point_count[s] = 1;
		}
		points.push_back(p);
		delete[] buff;
		start = temp_2 + 15;
	}
}
	
