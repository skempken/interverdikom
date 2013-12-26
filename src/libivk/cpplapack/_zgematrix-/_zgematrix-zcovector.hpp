//=============================================================================
/*! _zgematrix*zcovector operator */
inline _zcovector operator*(const _zgematrix& mat, const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zgematrix&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const _zgematrix&, const zcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector newvec(mat.M);
  zgemv_( 'N', mat.M, mat.N, std::complex<double>(1.0,0.0), mat.Array, mat.M,
          vec.Array, 1, std::complex<double>(0.0,0.0), newvec.array, 1 );
  
  mat.destroy();
  return _(newvec);
}
