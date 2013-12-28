//=============================================================================
/*! zhematrix*zcovector operator */
inline _zcovector operator*(const zhematrix& mat, const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zhematrix&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const zhematrix&, const zcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.N << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector newvec(mat.N);
  zhemv_( 'L', mat.N, std::complex<double>(1.0,0.0), mat.Array, mat.N,
          vec.Array, 1, std::complex<double>(0.0,0.0), newvec.array, 1 );
  
  return _(newvec);
}
