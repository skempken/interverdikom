//=============================================================================
/*! solve A*X=Y using zgesv\n
  The argument is zgematrix Y. Y is overwritten and become the solution X.
  A is also overwritten and become P*L*U. */
inline long zgematrix::zgesv(zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgesv(zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || M!=mat.M){
    std::cerr << "[ERROR] zgematrix::zgesv(zgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  long NRHS(mat.N), LDA(N), *IPIV(new long[N]), LDB(mat.M), INFO(1);
  zgesv_(N, NRHS, Array, LDA, IPIV, mat.Array, LDB, INFO);
  delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesv(zgematrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve A*x=y using zgesv\n
  The argument is zcovector y. y is overwritten and become the solution x.
  A is also overwritten and become P*L*U. */
inline long zgematrix::zgesv(zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgesv(zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || M!=vec.L){
    std::cerr << "[ERROR] zgematrix::zgesv(zcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  long NRHS(1), LDA(N), *IPIV(new long[N]), LDB(vec.L), INFO(1);
  zgesv_(N, NRHS, Array, LDA, IPIV, vec.Array, LDB, INFO);
  delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesv(zcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! solve overdetermined or underdetermined A*X=Y using zgels\n*/
inline long zgematrix::zgels(zgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgels(zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=mat.M){
    std::cerr << "[ERROR] zgematrix::zgels(zgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    zgematrix tmp(N,mat.N);
    for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  char TRANS('N');
  long NRHS(mat.N), LDA(M), LDB(mat.M),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgels_(TRANS, M, N, NRHS, Array, LDA, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    zgematrix tmp(N,mat.N);
    for(long i=0; i<tmp.M; i++){ for(long j=0; j<tmp.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgels(zgematrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*x=y using zgels\n*/
inline long zgematrix::zgels(zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgels(zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=vec.L){
    std::cerr << "[ERROR] zgematrix::zgels(zcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    zcovector tmp(N);
    for(long i=0; i<vec.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  char TRANS('N');
  long NRHS(1), LDA(M), LDB(vec.L),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgels_(TRANS, M, N, NRHS, Array, LDA, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    zcovector tmp(N);
    for(long i=0; i<tmp.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgels(zcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*X=Y using zgels
  with the sum of residual squares output\n
  The residual is set as the columnwise sum of residual squares 
  for overdetermined problems 
  while it is always zero for underdetermined problems.
*/
inline long zgematrix::zgels(zgematrix& mat, drovector& residual)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgels(zgematrix&, drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=mat.M){
    std::cerr << "[ERROR] zgematrix::zgels(zgematrix&, drovector&) "
              << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  residual.resize(mat.N); residual.zero();
  
  if(M<N){ //underdetermined
    zgematrix tmp(N,mat.N);
    for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  char TRANS('N');
  long NRHS(mat.N), LDA(M), LDB(mat.M),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgels_(TRANS, M, N, NRHS, Array, LDA, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    for(long i=0; i<residual.l; i++){ for(long j=0; j<M-N; j++){
      residual(i) += std::norm(mat(N+j,i));
    }}
    
    zgematrix tmp(N,mat.N);
    for(long i=0; i<tmp.M; i++){ for(long j=0; j<tmp.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgels(zgematrix&, drovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*x=y using zgels
  with the sum of residual squares output\n
  The residual is set as the sum of residual squares for overdetermined problems
  while it is always zero for underdetermined problems.
*/
inline long zgematrix::zgels(zcovector& vec, double& residual)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgels(zcovector&, double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=vec.L){
    std::cerr << "[ERROR] zgematrix::zgels(zcovector&, double&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  residual=0.0;
  
  if(M<N){ //underdetermined
    zcovector tmp(n);
    for(long i=0; i<vec.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  char TRANS('N');
  long NRHS(1), LDA(m), LDB(vec.L),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgels_(TRANS, M, N, NRHS, Array, LDA, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    for(long i=0; i<M-N; i++){ residual+=std::norm(vec(N+i)); }
    
    zcovector tmp(N);
    for(long i=0; i<tmp.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgels(zcovector&, double&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! calculate the least-squares-least-norm solution 
  for overdetermined or underdetermined A*x=y using zgelss\n */
inline long zgematrix::zgelss(zcovector& B, dcovector& S, long& RANK,
                              const double RCOND =-1. )
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgelss(zcovector&, dcovector&, long&, const double)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=B.L){
    std::cerr << "[ERROR] zgematrix::zgelss"
              << "(zcovector&, dcovector&, long&, const double) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << B.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    zcovector tmp(N);
    for(long i=0; i<B.L; i++){ tmp(i)=B(i); }
    B.clear();
    swap(B,tmp);
  }
  
  S.resize(min(M,N));
  
  long NRHS(1), LDA(M), LDB(B.L),
    LWORK(2*min(M,N) +max(max(M,N),NRHS)), INFO(1);
  double *RWORK(new double[5*min(M,N)]);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgelss_(M, N, NRHS, Array, LDA, B.Array, LDB, S.array, RCOND, RANK, 
          WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgelss"
              << "(zcovector&, dcovector&, long&, double) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate the least-squares-least-norm solution 
  for overdetermined or underdetermined A*x=y using zgelss\n */
inline long zgematrix::zgelss(zgematrix& B, dcovector& S, long& RANK,
                              const double RCOND =-1. )
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgelss(zgematrix&, dcovector&, long&, const double)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=B.M){
    std::cerr << "[ERROR] zgematrix::zgelss"
              << "(zgematrix&, dcovector&, long&, const double) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << B.M << "x" << B.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    zgematrix tmp(N,B.N);
    for(long i=0; i<B.M; i++){
      for(long j=0; j<B.N; j++){
        tmp(i,j)=B(i,j);
      }
    }
    B.clear();
    swap(B,tmp);
  }
  
  S.resize(min(M,N));
  
  long NRHS(B.N), LDA(M), LDB(B.M),
    LWORK(2*min(M,N) +max(max(M,N),NRHS)), INFO(1);
  double *RWORK(new double[5*min(M,N)]);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  zgelss_(M, N, NRHS, Array, LDA, B.Array, LDB, S.array, RCOND, RANK, 
          WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgelss"
              << "(zgematrix&, dcovector&, long&, const double) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! calculate eigenvalues\n
  The argument need not to be initialized.
  w is overwitten and become eigenvalues.
  This matrix is also overwritten. */
inline long zgematrix::zgeev(std::vector< std::complex<double> >& w)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgeev(std::vector< std::complex<double> >&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] zgematrix::zgeev"
              << "(std::vector<std::complex<double>>&) "
              << std::endl
              << "This matrix cannot have eigenvalues." << std::endl
              << "Your input was (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  w.resize(N);
  char JOBVL('N'), JOBVR('N');
  long LDA(N), LDVL(1), LDVR(1), LWORK(4*n), INFO(1);
  double *RWORK(new double[2*n]);
  std::complex<double> *VL(NULL), *VR(NULL), 
    *WORK(new std::complex<double>[LWORK]);
  zgeev_(JOBVL, JOBVR, N, Array, LDA, &w[0], 
         VL, LDVL, VR, LDVR, WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK; delete [] VL; delete [] VR;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesv"
              << "(std::vector<std::complex<double>&, std::vector<zcovector>&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate eigenvalues and right eigenvectors\n
  All of the arguments need not to be initialized.
  w, vr are overwitten and become eigenvalues and right eigenvectors, 
  respectively. 
  This matrix is also overwritten. */
inline long zgematrix::zgeev(std::vector< std::complex<double> >& w,
                             std::vector<zcovector>& vr)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgeev(std::vector< std::complex<double> >&, std::vector<zcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] zgematrix::zgeev"
              << "(std::vector<std::complex<double>>&, std::vector<zcovector>&)"
              << std::endl
              << "This matrix cannot have eigenvalues." << std::endl
              << "Your input was (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  w.resize(N);  vr.resize(N);
  for(long i=0; i<N; i++){ vr[i].resize(N); }
  zgematrix VR(N,N);
  char JOBVL('N'), JOBVR('V');
  long LDA(N), LDVL(1), LDVR(N), LWORK(4*n), INFO(1);
  double *RWORK(new double[2*n]);
  std::complex<double> *VL(NULL), *WORK(new std::complex<double>[LWORK]);
  zgeev_(JOBVL, JOBVR, N, Array, LDA, &w[0], 
         VL, LDVL, VR.Array, LDVR, WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK; delete [] VL;
  
  //// forming ////
  for(long j=0; j<N; j++){  for(long i=0; i<N; i++){
    vr[j](i) = VR(i,j);
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesv"
              << "(std::vector<std::complex<double>&, std::vector<zcovector>&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate eigenvalues and left eigenvectors\n
  All of the arguments need not to be initialized.
  w, vr are overwitten and become eigenvalues and left eigenvectors, 
  respectively. 
  This matrix is also overwritten. */
inline long zgematrix::zgeev(std::vector< std::complex<double> >& w,
                             std::vector<zrovector>& vl)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgeev(std::vector< std::complex<double> >&, std::vector<zrovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] zgematrix::zgeev"
              << "(std::vector<std::complex<double>>&, std::vector<zrovector>&)"
              << std::endl
              << "This matrix cannot have eigenvalues." << std::endl
              << "Your input was (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  w.resize(N);  vl.resize(N);
  for(long i=0; i<N; i++){ vl[i].resize(N); }
  zgematrix VL(N,N);
  char JOBVL('V'), JOBVR('N');
  long LDA(N), LDVL(N), LDVR(1), LWORK(4*n), INFO(1);
  double *RWORK(new double[2*n]);
  std::complex<double> *VR(NULL), *WORK(new std::complex<double>[LWORK]);
  zgeev_(JOBVL, JOBVR, N, Array, LDA, &w[0], 
         VL.Array, LDVL, VR, LDVR, WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK; delete [] VR;
  
  //// forming ////
  for(long j=0; j<N; j++){ for(long i=0; i<N; i++){
    vl[j](i) = std::conj(VL(i,j));
  }}
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesv"
              << "(std::vector<std::complex<double>&, std::vector<zrovector>&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
//inline long zgematrix::zgegv()


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! compute the singular value decomposition (SVD)\n
  The arguments are zcocector S, zgematrix U and VT.
  All of them need not to be initialized.
  S, U and VT are overwitten and become singular values, left singular vectors,
  and right singular vectors respectively.
  This matrix also overwritten.
*/
inline long zgematrix::zgesvd(dcovector& S, zgematrix& U, zgematrix& VT)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgematrix::zgesvd(dcovector&, zgematrix&, zgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  char JOBU('A'), JOBVT('A');
  long LDA(M), LDU(M), LDVT(N),
    LWORK(max(3*min(m,n)+max(m,n),5*min(m,n))), INFO(1);
  double *RWORK(new double[5*min(m,n)]);
  std::complex<double> *WORK(new std::complex<double>[LWORK]);
  S.resize(min(M,N)); U.resize(LDU,M); VT.resize(LDVT,N);
  
  zgesvd_(JOBU, JOBVT, M, N, Array, LDA, S.array, U.Array, 
          LDU, VT.Array, LDVT, WORK, LWORK, RWORK, INFO);
  delete [] RWORK; delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] zgematrix::zgesvd"
              << "(dceovector&, zgematrix&, zcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}
