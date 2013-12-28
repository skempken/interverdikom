//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void zgbmatrix::clear()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::clear()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgbmatrix::clear() "
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
inline void zgbmatrix::zero()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::zero()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =std::complex<double>(0.0,0.0); }
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline void zgbmatrix::identity()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::identity()"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(M!=N){
    std::cerr << "[ERROR] zgbmatrix::identity()" << std::endl
              << "Only square matrix can be a identity matrix." << std::endl
              << "The matrix size was " << M << "x" << N << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =std::complex<double>(0.0,0.0); }
  for(long i=0; i<M; i++){ operator()(i,i) =std::complex<double>(1.0,0.0); }
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void zgbmatrix::chsign()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::chsign()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  for(long i=0; i<(KL+KU+1)*N; i++){ Array[i] =-Array[i]; }
}
//=============================================================================
/*! make a deep copy of the matrix */
inline void zgbmatrix::copy(const zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::copy(const zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgbmatrix::copy(const zgbmatrix&) "
            << "A zgbmatrix at " << Array << " is going to be deleted. ";
#endif//CPPL_DEBUG
  
  M =mat.M;
  N =mat.N;
  KL =mat.KL;
  KU =mat.KU;
  delete [] Array;
  Array =new std::complex<double>[(mat.KL+mat.KU+1)*mat.N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }
  
  zcopy_((mat.KL+mat.KU+1)*mat.N, mat.Array, 1, Array, 1);
  
#ifdef  CPPL_DEBUG
  std::cerr << "Then, a COPY of a zgbmatrix has been cleated at "
            << Array << "." << std::endl;
#endif//CPPL_DEBUG
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void zgbmatrix::shallow_copy(const _zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::shallow_copy(const _zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] zgbmatrix::shallow_copy(const zgbmatrix&) "
            << "A zgbmatrix at " << Array << " is going to be deleted "
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
inline void zgbmatrix::resize(const long& _m, const long& _n,
                              const long& _kl, const long& _ku)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zgbmatrix::resize(const long&, const long&, const long&, const long&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 || _kl<0 || _ku<0 || _m<_kl || _n<_ku ){
    std::cerr << "[ERROR] zgbmatrix::resize"
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
  Array =new std::complex<double>[(KL+KU+1)*N];
  delete [] Darray;
  Darray =new std::complex<double>*[N];
  for(int i=0; i<N; i++){ Darray[i] =&Array[i*(KL+KU+1)]; }
}

//=============================================================================
/*! swap two matrices */
inline void swap(zgbmatrix& A, zgbmatrix& B)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] swap(zgbmatrix&, zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long A_m(A.M), A_n(A.N), A_kl(A.KL), A_ku(A.KU);
  std::complex<double>* A_array(A.Array);
  std::complex<double>** A_darray(A.Darray);
  A.M=B.M; A.N=B.N; A.KL=B.KL; A.KU=B.KU; A.Array=B.Array; A.Darray=B.Darray;
  B.M=A_m; B.N=A_n; B.KL=A_kl; B.KU=A_ku; B.Array=A_array; B.Darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zgbmatrix _(zgbmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _(zgbmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE

  _zgbmatrix newmat;

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
