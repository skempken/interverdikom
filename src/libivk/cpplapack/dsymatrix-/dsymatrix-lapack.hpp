//=============================================================================
/*! solve A*X=Y using dsysv\n
  The argument is dmatrix Y. Y is overwritten and become the solution X.
  A is also overwritten. 
*/
inline long dsymatrix::dsysv(dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsysv(dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=mat.N){
    std::cerr << "[ERROR] dsymatrix::dsysv(dgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << N << "x" << N << ") and ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  char UPLO('L');
  long NRHS(mat.N), LDA(N), *IPIV(new long[N]), LDB(mat.N), LWORK(-1), INFO(1);
  double *WORK( new double[1] );
  dsysv_(UPLO, N, NRHS, Array, LDA, IPIV, mat.Array, LDB, WORK, LWORK, INFO);
  
  INFO=1; 
  LWORK = long(WORK[0]);
  delete [] WORK;  WORK = new double[LWORK];
  dsysv_(UPLO, N, NRHS, Array, LDA, IPIV, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK; delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsysv(dsymatrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve A*x=y using dsysv\n
  The argument is dcovector y. y is overwritten and become the solution x.
  A is also overwritten.
*/
inline long dsymatrix::dsysv(dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsysv(dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(N!=vec.L){
    std::cerr << "[ERROR] dsymatrix::dsysv(dcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << N << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  char UPLO('L');
  long NRHS(1), LDA(N), *IPIV(new long[N]), LDB(vec.L), LWORK(-1), INFO(1);
  double *WORK( new double[1] );
  dsysv_(UPLO, N, NRHS, Array, LDA, IPIV, vec.Array, LDB, WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(WORK[0]);
  delete WORK;  WORK = new double[LWORK];
  dsysv_(UPLO, N, NRHS, Array, LDA, IPIV, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;  delete [] IPIV;

  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsysv(dcovector&) "
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
inline long dsymatrix::dsyev(std::vector<double>& w, const bool& jobz=0)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsyev(std::vector<double>&, const bool&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);
  char JOBZ, UPLO('L');
  if(jobz==0){ JOBZ='N'; } else{ JOBZ='V'; }
  long LDA(N), INFO(1), LWORK(-1);
  double *WORK(new double[1]);
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(WORK[0]);
  delete [] WORK;  WORK = new double[LWORK];
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsyev(vector<double>&, const bool&)"
              << std::endl
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
inline long dsymatrix::dsyev(std::vector<double>& w, std::vector<dcovector>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsyev(std::vector<double>&, std::vector<dcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);  v.resize(N);
  for(long i=0; i<N; i++){ v[i].resize(N); }
  char JOBZ('V'), UPLO('L');
  long LDA(N), INFO(1), LWORK(-1);
  double *WORK(new double[1]);
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(WORK[0]);
  delete [] WORK;  WORK = new double[LWORK];
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  delete [] WORK;
  
  //// forming ////
  for(long i=0; i<N; i++){ for(long j=0; j<N; j++){
    v[j](i) = Array[i+N*j];
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsyev"
              << "(vector<double>&, vector<dcovector>&)" << std::endl
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
inline long dsymatrix::dsyev(std::vector<double>& w, std::vector<drovector>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsyev(std::vector<double>&, std::vector<drovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  w.resize(N);  v.resize(N);
  for(long i=0; i<N; i++){ v[i].resize(N); }
  char JOBZ('V'), UPLO('L');
  long LDA(N), INFO(1), LWORK(-1);
  double *WORK(new double[1]);
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  
  INFO=1;
  LWORK = long(WORK[0]);
  delete [] WORK;  WORK = new double[LWORK];
  dsyev_(JOBZ, UPLO, N, Array, LDA, &w[0], WORK, LWORK, INFO);
  delete [] WORK;
  
  //// forming ////
  for(long i=0; i<N; i++){ for(long j=0; j<N; j++){
    v[j](i) = Array[i+N*j];
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsyev"
              << "(vector<double>&, vector<dcovector>&)" << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! calculate generalized eigenvalues\n
  w is overwitten and become generalized eigenvalues.
  This matrix and matB are also overwritten. 
*/
inline long dsymatrix::dsygv(dsymatrix& matB, std::vector<double>& w)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsygv(dsymatrix&, std::vector<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matB.N!=N){
    std::cerr << "[ERROR] dsymatrix::dsygv"
              << "(dsymatrix&, vector<double>&) " << std::endl
              << "The matrix B is not a matrix "
              << "having the same size as \"this\" matrix." << std::endl
              << "The B matrix is (" << matB.N << "x" << matB.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  w.resize(N);
  char JOBZ('N'), UPLO('L');
  long ITYPE(1), LDA(N), LDB(N), LWORK(-1), INFO(1);
  double *WORK(new double[1]);
  dsygv_(ITYPE, JOBZ, UPLO, N, Array, LDA, matB.Array, LDB, &w[0],
         WORK, LWORK, INFO);
  INFO=1;
  LWORK = long(WORK[0]);
  delete [] WORK;  WORK = new double[LWORK];
  dsygv_(ITYPE, JOBZ, UPLO, N, Array, LDA, matB.Array, LDB, &w[0],
         WORK, LWORK, INFO);
  delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsygv"
              << "(dsymatrix&, vector<double>&)"
              << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl
              << "Make sure that B matrix is a symmetric-definite."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate generalized eigenvalues\n
  w is overwitten and become generalized eigenvalues.
  This matrix and matB are also overwritten. 
*/
inline long dsymatrix::dsygv(dsymatrix& matB, std::vector<double>& w,
                             std::vector<dcovector>& v)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dsymatrix::dsygv(dsymatrix&, std::vector<double>&, std::vector<dcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(matB.N!=N){
    std::cerr << "[ERROR] dsymatrix::dsygv"
              << "(dsymatrix&, vector<double>&) " << std::endl
              << "The matrix B is not a matrix "
              << "having the same size as \"this\" matrix." << std::endl
              << "The B matrix is (" << matB.N << "x" << matB.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  w.resize(N);
  v.resize(N);
  char JOBZ('V'), UPLO('L');
  long ITYPE(1), LDA(N), LDB(N), LWORK(-1), INFO(1);
  double *WORK(new double[1]);
  dsygv_(ITYPE, JOBZ, UPLO, N, Array, LDA, matB.Array, LDB, &w[0],
         WORK, LWORK, INFO);
  INFO=1;
  LWORK = long(WORK[0]);
  std::cout << " LWORK = "  << LWORK  <<std::endl;
  delete [] WORK;  WORK = new double[LWORK];
  dsygv_(ITYPE, JOBZ, UPLO, N, Array, LDA, matB.Array, LDB, &w[0],
         WORK, LWORK, INFO);
  delete [] WORK;
  
  //// reforming ////
  for(int i=0; i<N; i++){
    v[i].resize(N);
    for(int j=0; j<N; j++){
      v[i](j) =Darray[i][j];
    }
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dsymatrix::dsygv"
              << "(dsymatrix&, vector<double>&)"
              << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl
              << "Make sure that B matrix is a symmetric-definite."
              << std::endl;
  }
  return INFO;
}
