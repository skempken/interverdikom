//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision General Band Matrix Class
class _zgbmatrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable long KL; //!< lower band width 
  mutable long KU; //!< upper band width 
  mutable std::complex<double>* Array; //!< 1D Array to store matrix data
  mutable std::complex<double>** Darray; //!< array of pointers of column head addresses
  
  //// constructor ////
  inline _zgbmatrix();
  inline _zgbmatrix(const _zgbmatrix&);
  inline ~_zgbmatrix(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _zgbmatrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _zgbmatrix t(const _zgbmatrix&);
  inline friend _zgematrix i(const _zgbmatrix&);
  inline friend _zgbmatrix conj(const _zgbmatrix&);
  inline friend _zgbmatrix conjt(const _zgbmatrix&);
  
  //// unary ////
  inline friend const _zgbmatrix& operator+(const _zgbmatrix&);
  inline friend _zgbmatrix operator-(const _zgbmatrix&);
  
  //// + ////
  inline friend _zgbmatrix operator+(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator+(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator+(const _zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator+(const _zgbmatrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const _zgbmatrix&);
  
  //// - ////
  inline friend _zgbmatrix operator-(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator-(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator-(const _zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator-(const _zgbmatrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const _zhematrix&, const _zgbmatrix&);
  
  //// * ////
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const _zgbmatrix&);
  inline friend _zgbmatrix operator*(const _zgbmatrix&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const _zgbmatrix&, const _zgbmatrix&);

  inline friend _zgematrix operator*(const _zgbmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const _zgematrix&);
  inline friend _zgematrix operator*(const  zgematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const _zgbmatrix&);
  
  inline friend _zgematrix operator*(const _zgbmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const _zhematrix&);
  inline friend _zgematrix operator*(const  zhematrix&, const _zgbmatrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const _zgbmatrix&);
  
  inline friend _zcovector operator*(const _zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgbmatrix&, const _zcovector&);
  inline friend _zrovector operator*(const  zrovector&, const _zgbmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zgbmatrix&);
  
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator*(const _zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator*(const     double&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const     double&, const _zgbmatrix&);
  
  inline friend _zgbmatrix operator*(const  zgbmatrix&, const std::complex<double>&);
  inline friend _zgbmatrix operator*(const _zgbmatrix&, const std::complex<double>&);
  inline friend _zgbmatrix operator*(const std::complex<double>&, const  zgbmatrix&);
  inline friend _zgbmatrix operator*(const std::complex<double>&, const _zgbmatrix&);
  
  //// / ////
  inline friend _zgbmatrix operator/(const  zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator/(const _zgbmatrix&, const     double&);
  inline friend _zgbmatrix operator/(const  zgbmatrix&, const std::complex<double>&);
  inline friend _zgbmatrix operator/(const _zgbmatrix&, const std::complex<double>&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
