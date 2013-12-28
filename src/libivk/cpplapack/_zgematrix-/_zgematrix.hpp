//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision General Dence Matrix Class
class _zgematrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable std::complex<double>* Array; //!< 1D Array to store matrix data
  mutable std::complex<double>** Darray; //!< array of pointers of column head addresses

  //// constructor ////
  inline _zgematrix();
  inline _zgematrix(const _zgematrix&);
  inline ~_zgematrix(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zgematrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _zgematrix t(const _zgematrix&);
  inline friend _zgematrix i(const _zgematrix&);
  inline friend _zgematrix conj(const _zgematrix&);
  inline friend _zgematrix conjt(const _zgematrix&);
  inline friend void idamax(long&, long&, const _zgematrix&);
  inline friend std::complex<double> damax(const _zgematrix&);
  
  //// unary ////
  inline friend const _zgematrix& operator+(const _zgematrix&);
  inline friend _zgematrix operator-(const _zgematrix&);
  
  //// + ////
  inline friend _zgematrix operator+(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const _zgematrix&);
  
  inline friend _zgematrix operator+(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const _zgematrix&);
  
  //// - ////
  inline friend _zgematrix operator-(const  zgematrix&);
  
  inline friend _zgematrix operator-(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const _zgematrix&);
  
  inline friend _zgematrix operator-(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zgbmatrix&);  
  inline friend _zgematrix operator-(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const _zgematrix&);
  
  //// * ////
  inline friend _zgematrix operator*(const  zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const _zgematrix&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const _zgematrix&);
  
  inline friend _zgematrix operator*(const  zcovector&, const  zrovector&);
  inline friend _zgematrix operator*(const  zcovector&, const _zrovector&);
  inline friend _zgematrix operator*(const _zcovector&, const  zrovector&);
  inline friend _zgematrix operator*(const _zcovector&, const _zrovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const _zgematrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zgematrix&);
  inline friend _zcovector operator*(const _zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgematrix&, const _zcovector&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const     double&);
  inline friend _zgematrix operator*(const _zgematrix&, const     double&);
  inline friend _zgematrix operator*(const     double&, const  zgematrix&);
  inline friend _zgematrix operator*(const     double&, const _zgematrix&);
  
  inline friend _zgematrix operator*(const  zgematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const _zgematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const std::complex<double>&, const  zgematrix&);
  inline friend _zgematrix operator*(const std::complex<double>&, const _zgematrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const std::complex<double>&);
  inline friend _zgematrix operator*(const std::complex<double>&, const  zhematrix&);

  //// / ////
  inline friend _zgematrix operator/(const  zgematrix&, const     double&);
  inline friend _zgematrix operator/(const _zgematrix&, const     double&);
  inline friend _zgematrix operator/(const  zgematrix&, const std::complex<double>&);
  inline friend _zgematrix operator/(const _zgematrix&, const std::complex<double>&);
  inline friend _zgematrix operator/(const  zhematrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zssmatrix;
  friend class _zssmatrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
