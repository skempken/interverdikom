//=============================================================================
/*! _zrovector*zhematrix operator */
inline _zrovector operator*(const _zrovector& vec, const zhematrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zrovector&, const zhematrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vec.L!=mat.N){
    std::cerr << "[ERROR] operator*(const zrovector&, const zhematrix&)"
              << std::endl
              << "These vector and matrix can not make a product."
              << std::endl
              << "Your input was (" << vec.L << ") * ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zrovector newvec(mat.N);
  zhemv_( 'L', mat.N, std::complex<double>(1.0,0.0), mat.Array, mat.N,
          vec.Array, 1, std::complex<double>(0.0,0.0), newvec.array, 1 );

  vec.destroy();
  return _(newvec);
}
