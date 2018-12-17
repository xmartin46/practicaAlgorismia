string pathString = "./20doc/";
	const char *path = pathString.c_str();
	vector<string> fileNames = list_dir(path);

	int nDocs = fileNames.size()