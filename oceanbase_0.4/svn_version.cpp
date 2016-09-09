const char* svn_version() { const char *SVN_Version = "0.42"; return SVN_Version; }
const char* build_date() { return __DATE__; }
const char* build_time() { return __TIME__; }
const char* build_flags() { return ""; }