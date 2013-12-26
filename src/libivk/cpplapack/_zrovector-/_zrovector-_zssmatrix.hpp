//=============================================================================
/*! _zrovector*_zssmatrix operator */
inline _zrovector operator*(const _zrovector& vec, const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zrovector&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vec.L!=mat.M){
    std::cerr << "[ERROR] operator*(const _zrovector&, const _zssmatrix&)"
              << std::endl
              << "These vector and matrix can not make a product."
              << std::endl
              << "Your input was (" << vec.L << ") * ("
              << mat.M << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zrovector newvec(mat.N);
  newvec.zero();
  
  for(int c=0; c<mat.VOL; c++){
    newvec(mat.Jndx[c]) +=vec(mat.Indx[c])*mat.Array[c];
  }
  
  vec.destroy();
  mat.destroy();
  return _(newvec);
}
