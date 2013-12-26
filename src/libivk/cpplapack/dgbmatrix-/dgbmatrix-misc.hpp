//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void dgbmatrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::clear() "
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG
  
  M =0;
  N =0;
  KL =0;
  KU =0;
  delete [] Array;
  Array =NULL;
  delete [] Darray;
  Darray =NULL;
}


//=============================================================================
/*! change the matrix into a zero matrix */
inline void dgbmatrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =0.0; }
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void dgbmatrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] dgbmatrix::identity()" << std::endl
              << "Only square matrix can be a identity matrix." << std::endl
              << "The matrix size was " << M << "x" << N << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =0.0; }
  for(long i=0; i<M; i++){ operator()(i,i) =1.0; }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void dgbmatrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =-Array[i]; }
}
//=============================================================================
/*! make a deep copy of the matrix */
inline void dgbmatrix::copy(const dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::copy(const dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::copy(const dgbmatrix&) "
            << "A dgbmatrix at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  KL =mat.KL;
  KU =mat.KU;
  delete [] Array;
  Array =new double[(mat.KL+mat.KU+1)*mat.N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }
  
  dcopy_((mat.KL+mat.KU+1)*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a dgbmatrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void dgbmatrix::shallow_copy(const _dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::shallow_copy(const _dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] dgbmatrix::shallow_copy(const dgbmatrix&) "
            << "A dgbmatrix at " << Array << " is going to be deleted "
            << "and point at " << mat.Array << " instead." << std::endl;
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  KL =mat.KL;
  KU =mat.KU;
  delete [] Array;
  Array =mat.Array;
  delete [] Darray;
  Darray =mat.Darray;
}

//=============================================================================
/*! resize the matrix */
inline void dgbmatrix::resize(const long& _m, const long& _n,
                              const long& _kl, const long& _ku)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dgbmatrix::resize(const long&, const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _kl<0 || _ku<0 || _m<_kl || _n<_ku ){
    std::cerr << "[ERROR] dgbmatrix::resize"
              << "(const long&, const long&, const long&, const long&)"
              << std::endl
              << "It is impossible to make a matrix you ordered. "
              << std::endl
              << "Your input was ("
              << _m << "," << _n << ","<< _ku << "," << _kl << ")."
              << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  M =_m;
  N =_n;
  KL =_kl;
  KU =_ku;
  delete [] Array;
  Array =new double[(KL+KU+1)*N];
  delete [] Darray;
  Darray =new double*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(dgbmatrix& A, dgbmatrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(dgbmatrix&, dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_m(A.M), A_n(A.N), A_kl(A.KL), A_ku(A.KU);
  double* A_array(A.Array);
  double** A_darray(A.Darray);
  A.M=B.M; A.N=B.N; A.KL=B.KL; A.KU=B.KU; A.Array=B.Array; A.Darray=B.Darray;
  B.M=A_m; B.N=A_n; B.KL=A_kl; B.KU=A_ku; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _dgbmatrix _(dgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(dgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _dgbmatrix newmat;
  
  newmat.M =mat.M;
  newmat.N =mat.N;
  newmat.KL =mat.KL;
  newmat.KU =mat.KU;
  newmat.Array =mat.Array;
  newmat.Darray =mat.Darray;
  
  mat.M =0;
  mat.N =0;
  mat.KL =0;
  mat.KU =0;
  mat.Array =NULL;
  mat.Darray =NULL;
  
  return newmat;
}
