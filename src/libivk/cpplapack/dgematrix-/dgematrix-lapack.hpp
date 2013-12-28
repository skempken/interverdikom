//=============================================================================
/*! solve A*X=Y using dgesv\n
  The argument is dgematrix Y. Y is overwritten and become the solution X.
  A is also overwritten and become P*L*U.
*/
inline long dgematrix::dgesv(dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgesv(dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || M!=mat.M){
    std::cerr << "[ERROR] dgematrix::dgesv(dgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  long NRHS(mat.N), LDA(N), *IPIV(new long[N]), LDB(mat.M), INFO(1);
  dgesv_(N, NRHS, Array, LDA, IPIV, mat.Array, LDB, INFO);
  delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgesv(dgematrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve A*x=y using dgesv\n
  The argument is dcovector y. y is overwritten and become the solution x.
  A is also overwritten and become P*L*U.
*/
inline long dgematrix::dgesv(dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgesv(dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N || M!=vec.L){
    std::cerr << "[ERROR] dgematrix::dgesv(dcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG 
  
  long NRHS(1), LDA(N), *IPIV(new long[N]), LDB(vec.L), INFO(1);
  dgesv_(N, NRHS, Array, LDA, IPIV, vec.Array, LDB, INFO);
  delete [] IPIV;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgesv(dcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! solve overdetermined or underdetermined A*X=Y using dgels\n
 */
inline long dgematrix::dgels(dgematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgels(dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=mat.M){
    std::cerr << "[ERROR] dgematrix::dgels(dgematrix&) " << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    dgematrix tmp(N,mat.N);
    for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  char TRANS('N');
  long NRHS(mat.N), LDA(M), LDB(mat.M),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgels_(TRANS, M, N, NRHS, Array, LDA, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    dgematrix tmp(N,mat.N);
    for(long i=0; i<tmp.M; i++){ for(long j=0; j<tmp.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgels(dgematrix&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*x=y using dgels\n
 */
inline long dgematrix::dgels(dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgels(dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=vec.L){
    std::cerr << "[ERROR] dgematrix::dgels(dcovector&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    dcovector tmp(N);
    for(long i=0; i<vec.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  char TRANS('N');
  long NRHS(1), LDA(M), LDB(vec.L),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgels_(TRANS, M, N, NRHS, Array, LDA, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    dcovector tmp(N);
    for(long i=0; i<tmp.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgels(dcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*X=Y using dgels
  with the sum of residual squares output\n
  The residual is set as the columnwise sum of residual squares 
  for overdetermined problems
  while it is always zero for underdetermined problems.
*/
inline long dgematrix::dgels(dgematrix& mat, drovector& residual)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgels(dgematrix&, drovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=mat.M){
    std::cerr << "[ERROR] dgematrix::dgels(dgematrix&, drovector&) "
              << std::endl
              << "These two matrices cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  residual.resize(mat.N); residual.zero();
  
  if(M<N){ //underdetermined
    dgematrix tmp(N,mat.N);
    for(long i=0; i<mat.M; i++){ for(long j=0; j<mat.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  char TRANS('N');
  long NRHS(mat.N), LDA(M), LDB(mat.M),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgels_(TRANS, M, N, NRHS, Array, LDA, mat.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    for(long i=0; i<residual.L; i++){ for(long j=0; j<M-N; j++){
      residual(i) += std::pow(mat(N+j,i), 2.0);
    }}
    
    dgematrix tmp(N,mat.N);
    for(long i=0; i<tmp.M; i++){ for(long j=0; j<tmp.N; j++){
      tmp(i,j) =mat(i,j);
    }}
    mat.clear();
    swap(mat,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgels(dgematrix&, drovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! solve overdetermined or underdetermined A*x=y using dgels
  with the sum of residual squares output\n
  The residual is set as the sum of residual squares 
  for overdetermined problems
  while it is always zero for underdetermined problems.
*/
inline long dgematrix::dgels(dcovector& vec, double& residual)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgels(dcovector&, double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=vec.L){
    std::cerr << "[ERROR] dgematrix::dgels(dcovector&, double&) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  residual=0.0;
  
  if(M<N){ //underdetermined
    dcovector tmp(N);
    for(long i=0; i<vec.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  char TRANS('N');
  long NRHS(1), LDA(M), LDB(vec.L),
    LWORK(min(M,N)+max(min(M,N),NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgels_(TRANS, M, N, NRHS, Array, LDA, vec.Array, LDB, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(M>N){ //overdetermined
    for(long i=0; i<M-N; i++){ residual+=std::pow(vec(N+i),2.0); }
    
    dcovector tmp(N);
    for(long i=0; i<tmp.L; i++){ tmp(i)=vec(i); }
    vec.clear();
    swap(vec,tmp);
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgels(dcovector&, double&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! calculate the least-squares-least-norm solution for overdetermined or 
  underdetermined A*x=y using dgelss\n
*/
inline long dgematrix::dgelss(dcovector& B, dcovector& S, long& RANK,
                              const double RCOND =-1. )
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgelss(dcovector&, dcovector&, long&, const double)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=B.L){
    std::cerr << "[ERROR] dgematrix::dgelss"
              << "(dcovector&, dcovector&, long, double) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << B.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    dcovector tmp(N);
    for(long i=0; i<B.L; i++){ tmp(i)=B(i); }
    B.clear();
    swap(B,tmp);
  }
  
  S.resize(min(M,N));
  
  long NRHS(1), LDA(M), LDB(B.L),
    LWORK(3*min(M,N)+max(max(2*min(M,N),max(M,N)), NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgelss_(M, N, NRHS, Array, LDA, B.Array, LDB, S.Array,
          RCOND, RANK, WORK, LWORK, INFO);
  delete [] WORK;

  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgelss"
              << "(dcovector&, docvector&, long, const double) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate the least-squares-least-norm solution for overdetermined or 
  underdetermined A*x=y using dgelss\n
*/
inline long dgematrix::dgelss(dgematrix& B, dcovector& S, long& RANK,
                              const double RCOND =-1. )
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgelss(dgematrix&, dcovector&, long& const double)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=B.M){
    std::cerr << "[ERROR] dgematrix::dgelss"
              << "(dgematrix&, dcovector&, long&, const double) " << std::endl
              << "These matrix and vector cannot be solved." << std::endl
              << "Your input was (" << M << "x" << N << ") and ("
              << B.M << "x" << B.N  << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG    
  
  if(M<N){ //underdetermined
    dgematrix tmp(N,B.N);
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
    LWORK(3*min(M,N)+max(max(2*min(M,N),max(M,N)), NRHS)), INFO(1);
  double *WORK(new double[LWORK]);
  dgelss_(M, N, NRHS, Array, LDA, B.Array, LDB, S.Array,
          RCOND, RANK, WORK, LWORK, INFO);
  delete [] WORK;

  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgelss"
              << "(dgematrix&, docvector&, long, const double) "
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
  All of the arguments need not to be initialized. 
  wr and wi are overwitten and become 
  real and imaginary part of eigenvalues, respectively. 
  This matrix is also overwritten. 
*/
inline long dgematrix::dgeev(std::vector<double>& wr, std::vector<double>& wi)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgeev(std::vector<double>&, std::vector<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&) " << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N);
  char JOBVL('N'), JOBVR('N');
  long LDA(N), LDVL(1), LDVR(1), LWORK(3*N), INFO(1);
  double *VL(NULL), *VR(NULL), *WORK(new double[LWORK]);
  dgeev_(JOBVL, JOBVR, N, Array, LDA, &wr[0], &wi[0], 
         VL, LDVL, VR, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VL; delete [] VL;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&)"
              << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate right eigenvalues and right eigenvectors\n
  All of the arguments need not to be initialized. 
  wr, wi, vrr, vri are overwitten and become 
  real and imaginary part of right eigenvalues and right eigenvectors, 
  respectively. 
  This matrix is also overwritten. 
*/
inline long dgematrix::dgeev(std::vector<double>& wr, std::vector<double>& wi, 
                             std::vector<dcovector>& vrr, 
                             std::vector<dcovector>& vri)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgeev(std::vector<double>&, std::vector<double>&, std::vector<dcovector>&, std::vector<dcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&, "
              << "vector<dcovector>&, vector<dcovector>&) "
              << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N); vrr.resize(N); vri.resize(N);
  for(long i=0; i<N; i++){ vrr[i].resize(N); vri[i].resize(N); }
  dgematrix VR(N,N);
  char JOBVL('N'), JOBVR('V');
  long LDA(N), LDVL(1), LDVR(N), LWORK(4*N), INFO(1);
  double *VL(NULL), *WORK(new double[LWORK]);
  dgeev_(JOBVL, JOBVR, N, Array, LDA, &wr[0], &wi[0], 
         VL, LDVL, VR.Array, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VL;
  
  //// forming ////
  for(long j=0; j<N; j++){
    if(fabs(wi[j])<1e-10){
      for(long i=0; i<N; i++){
        vrr[j](i) = VR(i,j);  vri[j](i) = 0.0;
      }
    }
    else{
      for(long i=0; i<N; i++){
        vrr[j](i)   = VR(i,j);  vri[j](i)   = VR(i,j+1);
        vrr[j+1](i) = VR(i,j);  vri[j+1](i) =-VR(i,j+1);
      }
      j++;
    }
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&, "
              << "vector<dcovector>&, vector<dcovector>&) "
              << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate left eigenvalues and left eigenvectors\n
  All of the arguments need not to be initialized. 
  wr, wi, vrr, vri are overwitten and become 
  real and imaginary part of left eigenvalues and left eigenvectors, 
  respectively. 
  This matrix is also overwritten. 
*/
inline long dgematrix::dgeev(std::vector<double>& wr, std::vector<double>& wi, 
                             std::vector<drovector>& vlr, 
                             std::vector<drovector>& vli)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgeev(std::vector<double>&, std::vector<double>&, std::vector<drovector>&, std::vector<drovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&, "
              << "vector<drovector>&, vector<drovector>&) "
              << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N); vlr.resize(N); vli.resize(N);
  for(long i=0; i<N; i++){ vlr[i].resize(N); vli[i].resize(N); }
  dgematrix VL(N,N);
  char JOBVL('V'), JOBVR('N');
  long LDA(N), LDVL(N), LDVR(1), LWORK(4*N), INFO(1);
  double *VR(NULL), *WORK(new double[LWORK]);
  dgeev_(JOBVL, JOBVR, N, Array, LDA, &wr[0], &wi[0], 
         VL.Array, LDVL, VR, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VR;

  //// forming ////
  for(long j=0; j<N; j++){
    if(fabs(wi[j])<1e-10){
      for(long i=0; i<N; i++){
        vlr[j](i) = VL(i,j);  vli[j](i) = 0.0;
      }
    }
    else{
      for(long i=0; i<N; i++){
        vlr[j](i)   = VL(i,j);  vli[j](i)   =-VL(i,j+1);
        vlr[j+1](i) = VL(i,j);  vli[j+1](i) = VL(i,j+1);
      }
      j++;
    }
  }
  

  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgeev"
              << "(vector<double>&, vector<double>&, "
              << "vector<drovector>&, vector<drovector>&) "
              << std::endl
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
  All of the arguments don't need to be initialized. 
  wr and wi are overwitten and become 
  real and imaginary part of generalized eigenvalues, respectively. 
  This matrix and matB are also overwritten. 
*/
inline long dgematrix::dggev(dgematrix& matB,
                             std::vector<double>& wr, std::vector<double>& wi)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dggev(dgematrix&, std::vector<double>&, std::vector<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&) " << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
  if(matB.M!=N || matB.N!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&) " << std::endl
              << "The matrix B is not a square matrix "
              << "having the same size as \"this\" matrix." << std::endl
              << "The B matrix is (" << matB.M << "x" << matB.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N);
  char JOBVL('N'), JOBVR('N');
  long LDA(N), LDB(N), LDVL(1), LDVR(1), LWORK(8*N), INFO(1);
  double *BETA(new double[N]), *VL(NULL), *VR(NULL), 
    *WORK(new double[LWORK]);
  dggev_(JOBVL, JOBVR, N, Array, LDA, matB.Array, LDB, &wr[0], &wi[0], 
         BETA, VL, LDVL, VR, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VL; delete [] VR;
  
  //// reforming ////
  for(long i=0; i<N; i++){ wr[i]/=BETA[i];  wi[i]/=BETA[i]; }
  delete [] BETA; 
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgeev"
              << "(dgematrix&, vector<double>&, vector<double>&)"
              << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate generalized eigenvalues and generalized right eigenvectors\n
  All of the arguments don't need to be initialized.
  wr, wi, vrr and vri are overwitten and become 
  real and imaginary part of generalized eigenvalue 
  and generalized right eigenvector, respectively. 
  This matrix and matB are also overwritten.
*/
inline long dgematrix::dggev(dgematrix& matB, 
                             std::vector<double>& wr, std::vector<double>& wi, 
                             std::vector<dcovector>& vrr, 
                             std::vector<dcovector>& vri)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dggev(dgematrix&, std::vector<double>&, std::vector<double>&, std::vector<dcovector>&, std::vector<dcovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<dcovector>&, vector<dcovector>&)" << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
  if(matB.M!=N || matB.N!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<dcovector>&, vector<dcovector>&)" << std::endl
              << "The matrix B is not a square matrix "
              << "having the same size as \"this\" matrix." << std::endl
              << "The B matrix is (" << matB.M << "x" << matB.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N); vrr.resize(N); vri.resize(N);
  for(long i=0; i<N; i++){ vrr[i].resize(N); vri[i].resize(N); }
  dgematrix VR(N,N);
  char JOBVL('N'), JOBVR('V');
  long LDA(N), LDB(N), LDVL(1), LDVR(N), LWORK(8*N), INFO(1);
  double *BETA(new double[N]), *VL(NULL), *WORK(new double[LWORK]);
  dggev_(JOBVL, JOBVR, N, Array, LDA, matB.Array, LDB, &wr[0], &wi[0], 
         BETA, VL, LDVL, VR.Array, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VL;
  
  //// reforming ////
  for(long i=0; i<N; i++){ wr[i]/=BETA[i];  wi[i]/=BETA[i]; }
  delete [] BETA; 
  
  //// forming ////
  for(long j=0; j<N; j++){
    if(fabs(wi[j])<1e-10){
      for(long i=0; i<N; i++){
        vrr[j](i) = VR(i,j);  vri[j](i) = 0.0;
      }
    }
    else{
      for(long i=0; i<N; i++){
        vrr[j](i)   = VR(i,j);  
        vri[j](i)   = VR(i,j+1);
        vrr[j+1](i) = VR(i,j);
        vri[j+1](i) =-VR(i,j+1);
      }
      j++;
    }
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<dcovector>&, vector<dcovector>&)" << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

//=============================================================================
/*! calculate generalized eigenvalues and generalized left eigenvectors\n
  All of the arguments don't need to be initialized.
  wr, wi, vlr and vli are overwitten and become 
  real and imaginary part of generalized eigenvalue 
  and generalized left eigenvector, respectively. 
  This matrix and matB are also overwritten.
*/
inline long dgematrix::dggev(dgematrix& matB, 
                             std::vector<double>& wr, std::vector<double>& wi, 
                             std::vector<drovector>& vlr, 
                             std::vector<drovector>& vli)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dggev(dgematrix&, std::vector<double>&, std::vector<double>&, std::vector<drovector>&, std::vector<drovector>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<drovector>&, vector<drovector>&)" << std::endl
              << "This matrix is not a square matrix." << std::endl
              << "This matrix is (" << M << "x" << N << ")." << std::endl;
    exit(1);
  }
  if(matB.M!=N || matB.N!=N){
    std::cerr << "[ERROR] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<drovector>&, vector<drovector>&)" << std::endl
              << "The matrix B is not a square matrix "
              << "having the same size as \"this\" matrix." << std::endl
              << "The B matrix is (" << matB.M << "x" << matB.N << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  wr.resize(N); wi.resize(N); vlr.resize(N); vli.resize(N);
  for(long i=0; i<N; i++){ vlr[i].resize(N); vli[i].resize(N); }
  dgematrix VL(N,N);
  char JOBVL('V'), JOBVR('N');
  long LDA(N), LDB(N), LDVL(N), LDVR(1), LWORK(8*N), INFO(1);
  double *BETA(new double[N]), *VR(NULL), *WORK(new double[LWORK]);
  dggev_(JOBVL, JOBVR, N, Array, LDA, matB.Array, LDB, &wr[0], &wi[0], 
         BETA, VL.Array, LDVL, VR, LDVR, WORK, LWORK, INFO);
  delete [] WORK; delete [] VR;
  
  //// reforming ////
  for(long i=0; i<N; i++){ wr[i]/=BETA[i];  wi[i]/=BETA[i]; }
  delete [] BETA; 
  
  //// forming ////
  for(long j=0; j<N; j++){
    if(fabs(wi[j])<1e-10){
      for(long i=0; i<N; i++){
        vlr[j](i) = VL(i,j);  vli[j](i) = 0.0;
      }
    }
    else{
      for(long i=0; i<N; i++){
        vlr[j](i)   = VL(i,j);  vli[j](i)   =-VL(i,j+1);
        vlr[j+1](i) = VL(i,j);  vli[j+1](i) = VL(i,j+1);
      }
      j++;
    }
  }
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dggev"
              << "(dgematrix&, vector<double>&, vector<double>&, "
              << "vector<drovector>&, vector<drovector>&)" << std::endl
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! compute the singular value decomposition (SVD)\n
  The arguments are dcocector S, dgematrix U and VT.
  All of them need not to be initialized.
  S, U and VT are overwitten and become singular values, 
  left singular vectors,
  and right singular vectors respectively.
  This matrix also overwritten.
*/
inline long dgematrix::dgesvd(dcovector& S, dgematrix& U, dgematrix& VT)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgematrix::dgesvd(dcovector&, dgematrix&, dgematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  char JOBU('A'), JOBVT('A');
  long LDA(M), LDU(M), LDVT(N),
    LWORK(max(3*min(M,N)+max(M,N),5*min(M,N))), INFO(1);
  double *WORK(new double[LWORK]);
  S.resize(min(M,N)); U.resize(LDU,M); VT.resize(LDVT,N);
  
  dgesvd_(JOBU, JOBVT, M, N, Array, LDA, S.Array, U.Array,
          LDU, VT.Array, LDVT, WORK, LWORK, INFO);
  delete [] WORK;
  
  if(INFO!=0){
    std::cerr << "[WARNING] dgematrix::dgesvd"
              << "(dceovector&, dgematrix&, dcovector&) "
              << "Serious trouble happend. INFO = " << INFO << "."
              << std::endl;
  }
  return INFO;
}
