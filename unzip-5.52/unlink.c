
int Xunlink(const char *p){
return unlink(p);}

int _getpid(void){return 55;}


int Xmkdir(const char *p){
return mkdir(p);}

int Xgetcwd(const char*p,int siz){
return getcwd(p,siz);
}
