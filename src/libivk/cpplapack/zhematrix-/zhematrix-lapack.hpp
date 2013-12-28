//=============================================================================
/*! solve A*X=Y using zhesv\n
  The argument is dmatrix Y. Y is overwritten and become the solution X.
  A is also overwritten. 
*/
inline long zhematrix::zhesv(zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhesv(zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] zhematrix::zhesv(zgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << N << "x" << N << ") and ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  char UPLO('L');
  long NRHS(mat.N), LDA(N), *IPIV(new long[N]), LDB(mat.N), LWORK(-1), INFO(1);
  std::complex<double> *WORK(new std::complex<double>[1]);
  zhesv_(UPLO, N, NRHS, Array, LDA, IPIV, mat.Array, LDB, WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(std::real(WORK[0]));
  delete [] WORK;  WORK =new std::complex<double>[LWORK];
  zhesv_(UPLO, N, NRHS, Array, LDA, IPIV, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK; delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zhematrix::zhesv(zhematrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve A*x=y using zhesv\n
  The argument is zcovector y. y is overwritten and become the solution x.
  A is also overwritten.
*/
inline long zhematrix::zhesv(zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zhesv(zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=vec.L){
    std::cerr << "[ERROR] zhematrix::zhesv(zcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << N << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  char UPLO('L');
  long NRHS(1), LDA(N), *IPIV(new long[N]), LDB(vec.L), LWORK(-1), INFO(1);
  std::complex<double> *WORK( new std::complex<double>[1] );
  zhesv_(UPLO, N, NRHS, Array, LDA, IPIV, vec.Array, LDB, WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(std::real(WORK[0]));
  delete WORK;  WORK = new std::complex<double>[LWORK];
  zhesv_(UPLO, N, NRHS, Array, LDA, IPIV, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;  delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zhematrix::zhesv(zcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! calculate eigenvalues and eigenvectors.\n
  All of the arguments need not to be initialized.
  w is overwitten and become eigenvalues.
  This matrix is also overwritten. 
  if jobz=1, this matrix becomes eigenvectors.
*/
inline long zhematrix::zheev(std::vector<double>& w,
                             const bool& jobz=0)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zheev(std::vector<double>&, const bool&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);
  char JOBZ, UPLO('L');
  if(jobz==0){ JOBZ='N'; } else{ JOBZ='V'; }
  long LDA(N), INFO(1), LWORK(-1);
  double *RWORK(new double[max(1, 3*N-2)]);
  std::complex<double> *WORK(new std::complex<double>[1]);
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  
  INFO=1;
  LWORK = long(std::real(WORK[0]));
  delete [] WORK;  WORK = new std::complex<double>[LWORK];
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  delete [] RWORK;  delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zhematrix::zheev"
              << "(vector<std::complex<double>>&, const bool&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate eigenvalues and eigenvectors.\n
  All of the arguments need not to be initialized.
  w and v are overwitten and become 
  eigenvalues and eigenvectors, respectively.
  This matrix is also overwritten. 
*/
inline long zhematrix::zheev(std::vector<double>& w,
                             std::vector<zcovector>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zheev(std::vector<double>&, std::vector<zcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);  v.resize(N);
  for(long i=0; i<N; i++){ v[i].resize(N); }
  char JOBZ('V'), UPLO('L');
  long LDA(N), INFO(1), LWORK(-1);
  double *RWORK(new double[max(1, 3*N-2)]);
  std::complex<double> *WORK(new std::complex<double>[1]);
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  
  INFO=1;
  LWORK = long(std::real(WORK[0]));
  delete [] WORK;  WORK = new std::complex<double>[LWORK];
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  delete [] RWORK;  delete [] WORK;
  
  //// forming ////
  for(long i=0; i<N; i++){ for(long j=0; j<N; j++){
    v[j](i) = Array[i+N*j];
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] zhematrix::zheev"
              << "(vector<std::complex<double>>&, vector<zcovector>&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate eigenvalues and eigenvectors.\n
  All of the arguments need not to be initialized.
  w and v are overwitten and become 
  eigenvalues and eigenvectors, respectively.
  This matrix is also overwritten. 
*/
inline long zhematrix::zheev(std::vector<double>& w,
                             std::vector<zrovector>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zhematrix::zheev(std::vector<double>&, std::vector<zrovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);  v.resize(N);
  for(long i=0; i<N; i++){ v[i].resize(N); }
  char JOBZ('V'), UPLO('L');
  long LDA(N), INFO(1), LWORK(-1);
  double *RWORK(new double[max(1, 3*N-2)]);
  std::complex<double> *WORK(new std::complex<double>[1]);
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  
  INFO=1;
  LWORK = long(std::real(WORK[0]));
  delete [] WORK;  WORK = new std::complex<double>[LWORK];
  zheev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, RWORK, INFO);
  delete [] RWORK;  delete [] WORK;
  
  //// forming ////
  for(long i=0; i<N; i++){ for(long j=0; j<N; j++){
    v[j](i) = Array[i+N*j];
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] zhematrix::zheev"
              << "(vector<std::complex<double>>&, vector<zcovector>&)"
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}
