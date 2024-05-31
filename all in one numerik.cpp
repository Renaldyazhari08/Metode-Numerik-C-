#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
struct notasi{
	bool v;
	double vs;
	bool n;
	double num;
	char t;
};

vector <notasi> subnotasi;

double f(double x){
	double hasil = 0;
	//int c = 1;
	//cout << "Iterasi Hasil sementara : \n";
	for (auto i : subnotasi){
	   // cout << "{" << i.v <<", "<<i.vs<<", "<<i.n<<", "<<i.num<<", " << i.t << "}\n";
		if (i.t == 'p'){
			if (i.v && i.n){
				hasil+=(i.num*pow(x,i.vs));
			}else{
				if (i.v){
					hasil+=pow(x, i.vs);
				}else{
					hasil+=i.num;
				}
			}
		}else{
			if (i.v && i.n){
				hasil-=(i.num*pow(x,i.vs));
			}else{
				if (i.v){
					hasil-=pow(x, i.vs);
				}else{
					hasil-=i.num;
				}
			}
		}
		//cout << c << ". Hsementara = " << hasil << endl;
		//c++;
	}
	//cout << endl;
	return hasil;
}

double bisecting(double x1, double x2, double xt, double e, int c){
	double f_xt = f(xt), f_x1 = f(x1), f_x2 = f(x2);
	cout << c << ". x1 = " << x1 << " | x2 = " << x2 << " | Xt = " << xt << " | f(x1) = " << f_x1 << " | f(x2) = " << f_x2  << " | f(Xt) = " << f_xt << " | " << ((f_xt*f_x1 < 0) ? "-" : "+" ) << endl;
	if (c == 5000){
		cout << "Iterasi Program sudah melebihi batas, mungkin metode ini tidak cocok untuk ekuasi yang ditujukan atau memang tidak ada solusi x nya dari ekuasi tersebut\n";
		cout << "Silahkan klik enter untuk melanjutkan\n";
		system("pause");
		return 87654321;
	}
	if (f_xt > 0 && f_xt <= e){
		return xt;
	}else if (abs(f_xt) > 0 && abs(f_xt) <= e){
		cout << "Nilai Absolut f(" << xt <<") = " << abs(f_xt) << " (lebih kecil dari 0.0001), Maka dengan ini solusi sudah mencapai titik optimal\n";
		return xt;
	}else if (f_xt == 0){
		cout << "Nilai f(" << xt <<") = " << f_xt << ", Maka Solusi dicapai dengan hasil yang analitik. Bila ingin hasil yang numerik, Bisa dicoba lagi dengan nilai awalan x1 dan x2 yang lain\n";
		return xt;
	}else{
		if (f_x1*f_xt < 0){
			return bisecting(x1, xt, (xt+x1)/2.0, e, c+1);
		}else if (f_x1*f_xt > 0){
			return bisecting(xt, x2, (xt+x2)/2.0, e, c+1);
		}
	}
}

double regulafalsi(double x1, double x2, double xt, double e, int c){
	double f_xt = f(xt), f_x1 = f(x1), f_x2 = f(x2);
	cout << c << ". x1 = " << x1 << " | x2 = " << x2 << " | Xt = " << xt << " | f(x1) = " << f_x1 << " | f(x2) = " << f_x2  << " | f(Xt) = " << f_xt << " | " << ((f_xt*f_x1 < 0) ? "-" : "+" ) << endl;
	if (f_xt > 0 && f_xt <= e){
		cout << "Solusi Numerik Ditemukan!\n";
		return xt;
	}else if (abs(f_xt) > 0 && abs(f_xt) <= e){
		cout << "Nilai absolut dari f(" << xt << ") = " << abs(f_xt) << " Lebih kecil dari 0.0001 dan lebih besar dari 0, Maka ini sudah mencapai solusi Numerik yang optimal\n";
		return xt;
	}else if (f_xt == 0){
		cout << "Nilai f(" << xt <<") = " << f_xt << ", Maka Solusi dicapai dengan hasil yang analitik. Bila ingin hasil yang numerik, Bisa dicoba lagi dengan nilai awalan x1 dan x2 yang lain\n";
		return xt;
	}else{
		if (f_x1 * f_xt > 0){
			return regulafalsi(xt, x2, xt-(f_xt*((x2-xt)/(f_x2-f_xt))), e, c+1);
		}else if (f_x1 * f_xt < 0){
			return regulafalsi(x1, xt, x1-(f_x1*((xt-x1)/(f_xt-f_x1))), e, c+1);
		}
	}
}

double f_inv(double x){
	double hasil = 0;
	//int c = 1;
	//cout << "Iterasi Hasil sementara : \n";
	for (auto i : subnotasi){
	   // cout << "{" << i.v <<", "<<i.vs<<", "<<i.n<<", "<<i.num<<", " << i.t << "}\n";
		if (i.t == 'p'){
			if (i.v && i.n){
				if (i.vs > 1){
					hasil+=(i.vs*i.num*pow(x, i.vs-1));
				}else{
					hasil+=(i.num);
				}
			}else{
				if (i.v){
					if (i.vs > 1){
						hasil+=(i.vs*pow(x, i.vs-1));
					}else{
						hasil+=1;					
					}
				}else{
					continue;
				}
			}
		}else{
			if (i.v && i.n){
				if (i.vs > 1){
					hasil-=(i.vs*i.num*pow(x, i.vs-1));
				}else{
					hasil-=(i.num);
				}
			}else{
				if (i.v){
					if (i.vs > 1){
						hasil-=(i.vs*pow(x, i.vs-1));
					}else{
						hasil-=1;					
					}
				}else{
					continue;
				}
			}
		}
		//cout << c << ". Hsementara = " << hasil << endl;
		//c++;
	}
	//cout << endl;
	return hasil;
}

double newton(double x_cur, double e, int c){
	double f_x = f(x_cur), finv_x = f_inv(x_cur);
	if (finv_x == 0){
		cout << "Hasil dari iterasi ke-" << c << " Membuahkan f'(" << x_cur <<") = 0, Hal ini membuat program error dikarenakan apapun yang nantinya dibagi 0 akan tidak terdefinisi\n";
		cout << "Silahkan tekan enter untuk mencoba lagi\n";
		system("pause");
		return 12345678;
	}else if (c == 5000){
		cout << "Hasil iterasi program sudah terlalu panjang, Mungkin untuk menemukan solusi X yang tepat tidak cocok menggunakan metode ini.\n";
		cout << "Silahkan tekan enter dan coba metode lainnya\n";
		system("pause");
		return 87654321;
	}
	double x2 = x_cur - (f_x/finv_x);
	double f_x2 = f(x2);
	cout << c << ". x1 = " << x_cur << " | f(x1) = " << f_x << " | f'(x1) = " << finv_x << " | x2 = " << x2 << " | f(x2) = " << f_x2 << endl; 
	if (f_x2 >= 0 && f_x2 <= e){
		if (f_x2 == 0){
			cout << "Solusi ditemukan namun dalam keadaan f(" << x2 << ") = " << f_x2 << ", Maka Ini adala Solusi yang bersifat analitik. Apabila ingin menemukan solusi yang numerik maka boleh diulangi lagi program ini\n";
		}else{
			cout << "Solusi Numerik Ditemukan!\n";
		}
		return x2;
	}else if(abs(f_x2) >= 0 && abs(f_x2) <= e){
		cout << "Solusi Absolute ditemukan!\n";
		return x2;
	}else{
		return newton(x2, e, c+1);
	}
}

double secant(double x1, double x2, double e, int c){
	double f_x1 = f(x1), f_x2 = f(x2);
	double x3 = x2-(f_x2*((x2-x1)/(f_x2-f_x1)));
	double f_x3 = f(x3);
	cout << c << ". x1 = " << x1 << " | x2 = " << x2 << " | x3 = " << x3 << " | f(x1) = " << f_x1 << " | f(x2) = " << f_x2  << " | f(x3) = " << f_x3 << endl; 
	if (0 <= f_x3 && f_x3 <= e){
		if (f_x3 == 0){
			cout << "Solusi Ditemukan, Namun ini adalah solusi analitik karena f(x3) = 0 \n";
			return x3;
		}else{
			cout << "Solusi Numerik Ditemukan!\n";
			return x3;
		}
	}else if(0 <= abs(f_x3) && abs(f_x3) <= e){
		cout << "Solusi Mutlak Numerik Ditemukan!\n";
		return x3;
	}else{
		return secant(x2, x3, e, c+1);
	}
}

vector <notasi> gsave;
notasi x_direct = {false, 1, false, 0, 'p'};

double g(double x, int acuan){
	bool negativitas = false;
	if (!x_direct.v){
		vector <notasi> g_tasi(subnotasi.begin(), subnotasi.end());
		x_direct = g_tasi[acuan];
		g_tasi.erase(g_tasi.begin()+acuan);
		bool reverse = true;
		if (x_direct.t == 'm'){
			reverse = false;
		}
		cout << "Persamaan Direct : " << (x_direct.t == 'm' ? ("-") : ("")) << (x_direct.n && x_direct.num > 1 ? (to_string((int)x_direct.num)+"x") : ("x")) << (x_direct.vs > 1 ? ("^"+to_string((int)x_direct.vs)+" = ") : (" = "));
		bool first = true;
		for (auto i : g_tasi){
			if (i.t == 'm'){
				if(first){
					//skip
				}else{
					cout << "+";
				}
			}else{
				cout << "-";
			}
			if (i.n){
				cout << i.num;
			}
			if(i.v){
				cout << "x";
			}
			if (i.vs > 1){
				cout << "^" << i.vs;
			}
			if (first){
				first = false;
			}
		}
		first = true;
		cout << "\nPersamaan Direct Setelah di sederhanakan : " << "x = " << ((int)x_direct.vs > 1 ? ("Akar "+to_string((int)x_direct.vs)+" Dari (") : "(");
		vector<notasi>temp_tasi(g_tasi.begin(), g_tasi.end());
		while (!temp_tasi.empty()){
			if (temp_tasi.front().t == 'm'){
				if (reverse){
					if (first){
						//skip
					}else{
						cout << "+";
					}
				}else{
					cout << "-";
				}
			}else{
				if (reverse){
					cout << "-";
				}else{
					if (first){
						//skip
					}else{
						cout << "+";
					}
				}
			}
			if (temp_tasi.front().n){
				cout << temp_tasi.front().num;
			}
			if(temp_tasi.front().v){
				cout << "x";
			}
			if (temp_tasi.front().vs > 1){
				cout << "^" << temp_tasi.front().vs;
			}
			if (first){
				first = false;
			}
			temp_tasi.erase(temp_tasi.begin());
		}
		cout <<")" << (x_direct.n ? "/"+to_string((int)x_direct.num)+"\n" : "\n");
		g_tasi.swap(gsave);
	}
	double hasil = 0;
	//int c = 1;
	for (auto i : gsave){
		if (i.t == 'p'){
			if (i.v && i.n){
				if (x_direct.t == 'p'){
					hasil-=(i.num*pow(x,i.vs));
				}else{
					hasil+=(i.num*pow(x,i.vs));
				}
			}else{
				if (i.v){
					if (x_direct.t == 'p'){
						hasil-=pow(x, i.vs);
					}else{
						hasil+=pow(x, i.vs);
					}
				}else{
					if (x_direct.t == 'p'){
						hasil-=i.num;
					}else{
						hasil+=i.num;
					}
				}
			}
		}else{
			if (i.v && i.n){
				if (x_direct.t == 'p'){
					hasil+=(i.num*pow(x,i.vs));
				}else{
					hasil-=(i.num*pow(x,i.vs));
				}
			}else{
				if (i.v){
					if (x_direct.t == 'p'){
						hasil+=pow(x, i.vs);
					}else{
						hasil-=pow(x, i.vs);
					}
				}else{
					if (x_direct.t == 'p'){
						hasil+=i.num;
					}else{
						hasil-=i.num;
					}
				}
			}
		}
		//cout << "Hasil Ke-" << c << " dari iterasi notasi : " << hasil << endl;
		//c++;
	}
	if (hasil < 0){
		negativitas = true;
	}
	if (x_direct.n){
		//cout << "Hasil akhir dibagi " << x_direct.num << " = ";
		hasil/=x_direct.num;
		//cout << hasil << endl;
	}
	if (x_direct.vs > 1){
		//cout << "Hasil akhir di akar pangkatkan " << x_direct.vs << " = ";
		if (negativitas){
			hasil = (pow(abs(hasil), 1.0/x_direct.vs))*-1;
		}else{
			hasil = pow(hasil, 1.0/x_direct.vs);	
		}
		//cout << hasil << endl;
	}
	return hasil;
}

double direct(double x1, double e, int c, int asn){
	//cout << "Subtitusi X = " << x1 << endl;
	double x2 = g(x1, asn);
	double ea = ((x2-x1)/x2);
	cout << c << ". x1 = " << x1 << " | x2 = " << x2 << " | ea(%) = " << ea << endl;
	if (c == 5000){
		return 87654321;
	}else if (0 <= ea && ea <= e){
		cout << "Solusi Numerik Ditemukan! dengan error " << ea*100 << "% \n";
		return x2;
	}else if (0 <= abs(ea) && abs(ea) <= e){
		cout << "Solusi Numerik Ditemukan! dengan error " << ea*100 << "% dan nilai absolut |x| = " << x2 << endl;
		return x2;
	}else{
		return direct(x2, e, c+1, asn);
	}
}

int main(){
	cout << "========================================================================\n"
		 << "      Selamat datang pada program All in One Metode Numerik\n"
		 << "                     Made by renaldy Azhari Imaduddin\n"
		 << "========================================================================\n"
		 << "Tekan enter untuk melanjutkan...\n";
	system("pause");
	res_eps:
	system("cls");
	cout << "===========================================================================\n"
		 << "			         Silahkan pilih Opsi pilihan epsilon\n"
		 << "===========================================================================\n"
		 << "1. Epsilon = 1\n"
		 << "2. Epsilon = 0.1\n"
		 << "3. Epsilon = 0.01\n"
		 << "4. Epsilon = 0.001\n"
		 << "5. Epsilon = 0.0001\n"
		 << "6. Epsilon = 0.00001\n";
	double e; int ce;
	string ekuasi;
	cout << "Masukan pilihan opsi : "; cin >> ce;
	switch (ce){
		case 1:
			e = 1;
			break;
		case 2:
			e = 0.1;
			break;
		case 3:
			e = 0.01;
			break;
		case 4:
			e = 0.001;
			break;
		case 5:
			e = 0.0001;
			break;
		case 6:
			e = 0.00001;
			break;
		default:
			goto res_eps;
			break;
	}
	res_notasi:
	cout << "Masukan notasi Ekuasi : "; cin.ignore(); getline(cin, ekuasi);
	while (ekuasi.find(" ") != -1){
		ekuasi.erase(ekuasi.find(" "), 1);
	}
	while (ekuasi.find("{") != -1){
		ekuasi.erase(ekuasi.find("{"), 1);
	}
	while (ekuasi.find("}") != -1){
		ekuasi.erase(ekuasi.find("}"), 1);
	}
	while (ekuasi.find("(") != -1){
		ekuasi.erase(ekuasi.find("("), 1);
	}
	while (ekuasi.find(")") != -1){
		ekuasi.erase(ekuasi.find(")"), 1);
	}
	int len = ekuasi.length();
	bool traverse[len], xyes = false, unde = false, salah = false, minstart = false,
		dobel_num = false, dobel_x = false, salpang = false, misxplace = false, misxsplace = false,
		null_xs = false, null_subn = false;
	memset(traverse, false, sizeof(traverse));
	string sdobel_num, sdobel_x, ssalpang, smisxplace, smisxsplace, snull_xs;
	notasi matemp = {false, 1, false, 0, 'p'};
	if (ekuasi[0] == '-'){
		minstart = true;
		xyes = true;
		salah = true;
	}
	for (int i = 0; i <= len; i++){
		//cout << "Iterasi char ke-" << i << ", Yakni : " << ekuasi[i] << endl;
	    if (i == len || salah){
	    	//cout << salah ? "salah ditemukan\n" : "No salah";
			subnotasi.push_back(matemp);
			/*cout << "xyes  = " << xyes << endl 
				 << "unde = " << unde << endl
				 << "minstart = " << minstart << endl
				 << "dobel_num = " << dobel_num << endl 
				 << "dobel_x = " << dobel_x << endl
				 << "salpang = " << salpang << endl 
				 << "misxplace = " << misxplace << endl
				 << "misxsplace = " << misxsplace << endl
				 << "null_xs = " << null_xs << endl
				 << "null_subn = " << null_subn << endl;*/
			break;
		}
		if (!traverse[i]){
			//cout << 1 << endl;
			traverse[i] = true;
			if (!(('0' <= ekuasi[i] && ekuasi[i] <= '9') || (ekuasi[i] =='x' || ekuasi[i] == 'X') || (ekuasi[i] == '+' || ekuasi[i] == '-'))){
				//cout << 2 << endl;
				unde = true;
				salah = true;
			}
			if ('0' <= ekuasi[i] && ekuasi[i] <= '9'){
				//cout << 3 << endl;
			    //cout << "subnotasi baru terdeteksi!";
			    if (!matemp.n){
			    	//cout << 4 << endl;
				    matemp.n = true;
					string temp(1,ekuasi[i]);
					int c = 1;
					if (('0' <= ekuasi[i+c] && ekuasi[i+c] <= '9') || (ekuasi[i+c] == '^') && i+c < len){
						//cout << 5 << endl;
						while ((('0' <= ekuasi[i+c] && ekuasi[i+c] <= '9') || (ekuasi[i+c] == '^')) && i+c < len){
							//cout << 6 << endl;
							if (ekuasi[i+c] == '^'){
								//cout << 7 << endl;
								salpang = true;
								salah = true;
								int dd = i;
								while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
									dd--;
								}
								ssalpang += ekuasi[dd++];
								while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
									ssalpang+=ekuasi[dd++];
								}
								break;
							}else{
								//cout << 8 << endl;
								traverse[i+c] = true;
								temp+=ekuasi[i+c];
								c++;
							}
						}
					}
					//cout << " subnotasi = " << temp << endl;
					matemp.num = stoi(temp);
				}else{
					//cout << 9 << endl;
					dobel_num = true;
					salah = true;
					int dd = i;
					while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
						dd--;
					}
					sdobel_num += ekuasi[dd++];
					while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
						sdobel_num+=ekuasi[dd++];
					}
					break;
				}
			}else if(ekuasi[i] =='x' || ekuasi[i] == 'X'){
				//cout << 10 << endl;
				if (!matemp.v){
					//cout << 11 << endl;
					if (!xyes){
						//cout << 12 << endl;
						xyes = true;
					}
					if (!subnotasi.empty() && subnotasi.back().v == false){
						//cout << 13 << endl;
						misxplace = true;
						salah = true;
						int dd = i;
						while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
							dd--;
						}
						dd--;
						while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
							dd--;
						}
						smisxplace += ekuasi[dd++];
						while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
							smisxplace+=ekuasi[dd++];
						}
						smisxplace += ekuasi[dd++];
						while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
							smisxplace+=ekuasi[dd++];
						}
						break;
					}
					matemp.v = true;
					int c = 1;
					//cout << "X Terdeteksi!";
					if (ekuasi[i+c] == '^'){
						//cout << 14 << endl;
						traverse[i+c] = true;
						c++;
						string temp;
						if ('0' <= ekuasi[i+c] && ekuasi[i+c] <= '9' && i+c < len){
							//cout << 15 << endl;
							while ('0' <= ekuasi[i+c] && ekuasi[i+c] <= '9' && i+c < len){
								traverse[i+c] = true;
								temp+=ekuasi[i+c];
								c++;
							}
						}else{
							//cout << 16 << endl;
							null_xs = true;
							salah = true;
							int dd = i;
							while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
								dd--;
							}
							snull_xs += ekuasi[dd++];
							while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
								snull_xs+=ekuasi[dd++];
							}
							continue;
						}
						matemp.vs = stoi(temp);
						if (!subnotasi.empty() && subnotasi.back().vs < matemp.vs){
							//cout << 17 << endl;
							misxsplace = true;
							salah = true;
							int dd = i;
							while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
								dd--;
							}
							dd--;
							while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
								dd--;
							}
							smisxsplace += ekuasi[dd++];
							while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
								smisxsplace+=ekuasi[dd++];
							}
							smisxsplace += ekuasi[dd++];
							while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
								smisxsplace+=ekuasi[dd++];
							}
							continue;
						}
					}
					//cout << "X^" << matemp.vs << endl; 
				}else{
					//cout << 18 << endl;
					dobel_x = true;
					salah = true;
					int dd = i;
					while (ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != 0){
						dd--;
					}
					sdobel_x += ekuasi[dd++];
					while(ekuasi[dd] != '-' && ekuasi[dd] != '+' && dd != len){
						sdobel_x+=ekuasi[dd++];
					}
					continue;
				}
			}else if (ekuasi[i] == '+' || ekuasi[i] == '-'){
				//cout << 19 << endl;
				if (matemp.n || matemp.v){
					//cout << 20 << endl;
					subnotasi.push_back(matemp);
					//cout << "\nSub-Notasi Baru Terdeteksi!\n";
				}else{
					//cout << 21 << endl;
					null_subn = true;
					salah = true;	
					continue;
				}
				if (ekuasi[i] == '+'){
					//cout << 22 << endl;
					matemp = {false, 1, false, 0, 'p'};
				}else{
					//cout << 23 << endl;
					matemp = {false, 1, false, 0, 'm'};
				}
			}
		}
	}
	if (!xyes){
		salah = true;
	}
	if (salah){
		if (!xyes){
			cout << "Tidak terdeteksi Variabel X dalam ekuasi Polinomial yang anda ketik, silahkan coba lagi dengan mengingat untuk menginput variabel x didalam ekuasi nanti\n";	
		}
		if (unde){
			cout << "Ada Karakter yg tidak dikenali oleh program, Ingat untuk memasukan notasi rumus ekuasi secara matematis hanya dengan : \n"
				 << "Angka 0 sampai 9\n"
				 << "X atau x\n"
				 << "^ (simbol untuk pangkat dan di-input hanya pada saat setelah menginput variabel x)\n"
				 << "+ atau -\n\n";
		}
		if (minstart){
			cout << "Terdeteksi ekuasi polinomial di awali dengan negatif, Hal ini tidak bisa diterima oleh program karena penulisan polinomial yang tidak matematis. Silahkan coba lagi dengan mengkalikan ekuasi dengan negatif\n"
				 << "Dengan mengkali ekuasi dengan -1, ekuasi menjadi : ";
				 string negakuasi;
				 for (int i = 1; i < len; i++){
				 	if (ekuasi[i] == '+' || ekuasi[i] == '-'){
				 		if (ekuasi[i] == '+'){
				 			negakuasi+='-';
						}else{
							negakuasi+='+';
						}
					}else{
						negakuasi+=ekuasi[i];
					}
				 }
			cout << negakuasi << endl;
		}
		if (dobel_num){
			cout << "Terdeteksi Sub-Notasi Ekuasi yang mempunyai lebih dari satu koeffisien yakni : " << sdobel_num << endl;
			cout << "Sub-notasi tidak boleh mempunyai lebih dari 1 koeffisien agar ekuasi bisa diterima oleh program\n";
			cout << "Bila anda bermaksud menuliskan x pangkat <nomer>, Silahkan gunakan karakter `^` sebagai pembeda antara variabel x dan nomer pangkat\n";
		}
		if (dobel_x){
			cout << "Terdeteksi Sub-Notasi Ekuasi yang mempunyai lebih dari satu variabel x yakni : " << sdobel_x << endl;
			cout << "Sub-notasi tidak boleh mempunyai lebih dari satu variabel x agar bisa diterima oleh program\n";
		}
		if (salpang){
			cout << "Terdeteksi Sub-notasi ekuasi yang mempunyai Koeffisien berpangkat, Yakni : " << ssalpang << endl
				 << "Sub-notasi tidak boleh mempunyai Koeffisien yang berpangkat agar bisa diterima oleh program\n"
				 << "Silahkan operasikan terlebih dahulu sendiri agar bilangan/koeffisien tersebut sudah dalam berbentuk tak berpangkat ketika di-input kepada ekuasi polinomial program\n";
		}
		if (misxplace){
			cout << "Terdeteksi Sub-Notasi ekuasi yang dimana pada sub-notasi tersebut ada posisi variabel x yang ada setelah sub-notasi sebelumnya yang tak mempunyai x, yakni :" << smisxplace << endl
				 << "Tidak boleh ada Sub-Notasi yang mempunyai variabel x yang terletak setelah Sub-Notasi Sebelumnya yang tak mempunyai variabel x agar dapat diterima oleh program\n";
		}
		if (null_xs){
			cout << "Terdeteksi Sub-Notasi ekuasi yang dimana pada sub-notasi tersebut ada posisi variabel x yang memiliki pangkat tak jelas, yakni : "<< snull_xs << endl
				 << "Tidak boleh ada Sub-Notasi yang mempunyai variabel x yang berpangkat tak jelas agar dapat diterima oleh program\n";
		}
		if (misxsplace){
			cout << "Terdeteksi Sub-Notasi ekuasi yang dimana pada sub-notasi tersebut ada posisi variabel x berpangkat lebih besar dari variabel x pada sub-notasi sebelumnya, yakni : " << smisxsplace << endl
				 << "Tidak boleh ada Sub-Notasi yang mempunyai variabel x berpangkat lebih besar dari Pangkat Variabel x pada Sub-Notasi Sebelumnya agar dapat diterima oleh program\n";
		}
		if (null_subn){
			cout << "Terdeteksi sebuah Sub-Notasi dari ekuasi yang tidak memiliki koefisien maupun variabel x\n"
				 << "Hal ini disebabkan karena anda mengetik operator (+) atau (-) saling berbandingan tanpa ada koefiesien maupun variabel x yang mendampingi operator tersebut\n"
				 << "Tidak Boleh ada Sub-Notasi ekuasi yang tidak memiliki sama sekali variabel x dan koeffisien agar dapat diterima oleh program\n";
		}
		cout << "Contoh notasi ekuasi yang memenuhi persyaratan penulisan matematis sesuai program ini : \n"
			 << "x^2-2x+1\n"
			 << "X^2-25\n"
			 << "X^3+3X^2-x-7\n"
			 << "Dan lain sebagainya.... (Tidak ada batasan pola polinomial)\n"
			 << "Ingat juga untuk tidak menambahkan `= 0` diakhir ekuasi karena program akan otomatis menganggap ekuasi sudah sama dengan 0\n";
		subnotasi.clear();
		memset(traverse, false, sizeof(traverse));
		xyes = false, unde = false, salah = false, minstart = false,
		dobel_num = false, dobel_x = false, salpang = false, misxplace = false, misxsplace = false,
		null_xs = false, null_subn = false;
		cout << "Silahkan klik tombol enter untuk mengulangi lagi pemasukan ulang rumus notasi ekuasi\n";
		system("pause");
		system("cls");
		goto res_notasi;
	}
	res_method:
	cout << "Pilihlah metode numerik dengan angka :\n"
		 << "1. Metode Bisection\n"
		 << "2. Metode Regulafalsi\n"
		 << "3. Metode Newton\n"
		 << "4. Metode Secant\n"
		 << "5. Metode Direct\n"
		 << "6, 7, 8... Coming soon (Akan ditambahkan nanti)\n";
	cout << "Pilih metode : "; int q; cin >> q;
	restart_calculate:
	system("cls");
	cout << "Formula ekuasi : " << ekuasi << " = 0\n";
	switch(q){
		double x1,x2, ans;
		int c, cq;
		case 1:
			cout << "Masukan Nilai X1 = "; cin >> x1;
			cout << "Masukan Nilai X2 = "; cin >> x2;
			c = 0;
			while (!(f(x1) * f(x2) < 0)){
				if (c == 5){
					cout << "Anda Sudah memasukan nilai x1 dan x2 selama 5 kali dan tetap nilai f(x1)*f(x2) tidak menghasilkan lebih kecil dari 0\n";
					cout << "Anda akan dipindahkan ke pilihan program, klik enter untuk melanjutkan\n";
					system("pause");
					system("cls");
					goto pilih_ulang;
				}
				cout << "\n\nNilai f(x1) * f(x2) tidak Menghasilkan lebih kecil dari 0 !\n";
				cout << "Masukan Kembali Nilai X1 = "; cin >> x1;
				cout << "Masukan kembali Nilai X2 = "; cin >> x2;
				c++;
			}
			ans = bisecting(x1, x2, (x1+x2)/2, e, 1);
			if (ans == 87654321){
				goto pilih_ulang;
			}else{
				cout << "Solusi Xt = " << ans << endl;
			}
			break;
		case 2:
			cout << "Masukan Nilai X1 = "; cin >> x1;
			cout << "Masukan Nilai X2 = "; cin >> x2;
			while (!(f(x1) * f(x2) < 0)){
				cout << "\n\nNilai f(x1) * f(x2) tidak Menghasilkan lebih kecil dari 0 !\n";
				cout << "Masukan Kembali Nilai X1 = "; cin >> x1;
				cout << "Masukan kembali Nilai X2 = "; cin >> x2;
			}
			cout << "Solusi Xt = " << regulafalsi(x1, x2, x1 - (f(x1) * ((x2-x1)/(f(x2)-f(x1)))), e, 1) << endl;
			break;
		case 3:
			cout << "Masukan Nilai X awal = "; cin >> x1;
			ans = newton(x1, e, 1);
			if (ans == 12345678 || ans == 87654321){
				goto pilih_ulang;
			}else{
				cout << "Solusi x = " << ans << endl;
			}
			break;
		case 4:
			cout << "Masukan nilai sembarang awal\n";
			cout << "Masukan Nilai X1 = "; cin >> x1;
			cout << "Masukan Nilai X2 = "; cin >> x2;
			cout << "Solusi X = " << secant(x1, x2, e, 1) << endl;
			break;
		case 5:
			res_direct:
			cout << "Silahkan pilih Sub-notasi dari Notasi Ekuasi polinomial yang tadi anda ketik yang nantinya akan dijadikan acuan\n"
				 << "Ekuasi Notasi Polinomial : " << ekuasi << endl
				 << "Pilihan Sub-Notasi yang bisa dijadikan ekuasi : \n";
				 c = 1;
			for (auto i : subnotasi){
				if (i.v){
					cout << "Pilihan Ke-" << c << " = " << (i.t == 'p' ? (c == 1 ? ("") : ("+")) : ("-")) << (i.n ? (to_string((int)i.num)+"x") : ("x")) << (i.vs > 1 ? ("^"+to_string((int)i.vs)) : ("\n")) << endl;
					c++;
				}
			}
			cout << "Pilihan anda : "; cin >> cq;
			if (!(1 <= cq && cq <= c-1)){
				cq_direct:
				cout << "Maaf Pilihan anda Tidak terdefinisi, Apakah anda ingin mencoba lagi?\n"
					 << "1. Coba pilih lagi acuan Sub-Notasi\n"
					 << "2. Kembali Ke Menu utama\n"
					 << "Pilih : "; cin >> cq;
					 if (cq == 1){
						system ("cls");
						goto res_direct;
					 }else if (cq == 2){
						system("cls");
						goto pil_restart;
					 }else{
						system("cls");
						goto cq_direct;
					 }
			}
			cout << "Masukan nilai X awal = "; cin >> x1;
			ans = direct(x1, e, 1, cq-1);
			if (ans == 87654321){
				cout << "Hasil iterasi program sudah terlalu panjang, Mungkin karena tidak adanya solusi x atau metode ini tidak cocok untuk menemukan solusi X dari " << ekuasi << " = 0 \n";
				cout << "Silahkan tekan enter untuk melanjutkan\n";
				system("pause");
				x_direct = {false, 1, false, 0, 'p'};
				gsave.clear();
				system("cls");
				goto pilih_ulang;
			}else{
				cout << "Solusi X = " << ans << endl;
			}
			x_direct = {false, 1, false, 0, 'p'};
			gsave.clear();
			break;
		default:
			cout << "Pilihan tidak ada, Coba lagi dengan nomor yang sesuai daftar metode.\n";
			goto res_method;
			break;
	}
	pilih_ulang:
	char choose;
	cout << "Apakah anda ingin mengulangi kembali program ini? [y/n] : "; cin >> choose;
	if (choose == 'y' || choose == 'Y'){
		system("cls");
		pil_restart:
		cout << "Ingin mengulangi dari bagian mana? : \n"
			 << "1. Ulangi dari pemasukan epsilon\n"
			 << "2. Ulangi dari pemasukan notasi ekuasi persamaan\n"
			 << "3. Ulangi dari Pemilihan metode & penginputan nilai awal sembarang x\n";
		int respil;
		cout << "Pilih : "; cin >> respil;
		switch (respil){
			case 1:
				system("cls");
				subnotasi.clear();
				memset(traverse, false, sizeof(traverse));
				matemp = {false, 1, false, 0, 'p'};
				goto res_eps;
				break;
			case 2:
				system("cls");
				subnotasi.clear();
				memset(traverse, false, sizeof(traverse));
				matemp = {false, 1, false, 0, 'p'};
				goto res_notasi;
				break;
			case 3:
				system("cls");
				goto res_method;
				break;
			default:
				cout << "Pilihan anda tidak sesuai daftar ulangi program, Coba pilih lagi yang sesuai.\n";
				system("pause");
				goto pil_restart;
				break;
		}
	}else{
		cout << "Terimakasih Telah menggunakan Algoritma yang saya buat!\n"
			 << "Creator & Copyrights owner : Renaldy Azhari Imaduddin\n";
		exit(0);
	}
}
