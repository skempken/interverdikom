//=============================================================================
//! Complex Double-precision Sparse Matrix Class
class zssmatrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  long CAP; //!< the length of data arrays (NOT accessible)
  long VOL; //!< the number of non-zero components (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store non-zero matrix data (NOT accessible)
  long* Indx; //!< 1D array to store the i-index of non-zero matrix components (NOT accessible)
  long* Jndx; //!< 1D array to store the j-index of non-zero matrix components (NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  long const& cap; //!<  the length of data arrays (readable)
  long const& vol; //!< the number of non-zero components (readable)
  std::complex<double>* const& array; //!< 1D array to store matrix data (readable)
  long* const& indx; //!< 1D array to store the i-index of non-zero matrix components (readable)
  long* const& jndx; //!< 1D array to store the j-index of non-zero matrix components (readable)
  
  //// constructor ////
  inline zssmatrix();
  inline zssmatrix(const zssmatrix&);
  inline zssmatrix(const _zssmatrix&);
  inline zssmatrix(const long&, const long&, const long&);
  inline zssmatrix(const char*);
  inline ~zssmatrix(); //destructor
  
  //// cast ////
  inline operator _zgematrix();
  
  //// io ////
  inline std::complex<double> operator()(const long&, const long&) const;
  inline void put(const long&, const long&, const std::complex<double>&);
  inline void fput(const long&, const long&, const std::complex<double>&);
  inline void add(const long&, const long&, const std::complex<double>&);
  inline void sub(const long&, const long&, const std::complex<double>&);
  inline void mult(const long&, const long&, const std::complex<double>&);
  inline void div(const long&, const long&, const std::complex<double>&);
  inline void del(const long&, const long&);
  inline void fdel(const long&);
  inline friend std::ostream& operator<<(std::ostream&, const zssmatrix&);
  inline void write(const char *) const;
  inline void read(const char *);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const zssmatrix&);
  inline void shallow_copy(const _zssmatrix&);
  inline void resize(const long&, const long&, const long&);
  inline void expand(const long&);
  inline bool isListed(const long&, const long&);
  inline long number(const long&, const long&);
  inline void checkup();
  inline friend void swap(zssmatrix&, zssmatrix&);
  inline friend _zssmatrix _(zssmatrix&);
  
  //// calc ////
  inline friend _zssmatrix t(const zssmatrix&);
  inline friend void idamax(long&, long&, const zssmatrix&);
  inline friend std::complex<double> damax(const zssmatrix&);
  
  //// unary ////
  inline friend const zssmatrix& operator+(const zssmatrix&);
  inline friend _zssmatrix operator-(const zssmatrix&);
  
  //// operators with zssmatrix ////
  inline zssmatrix& operator=(const zssmatrix&);
  inline zssmatrix& operator+=(const zssmatrix&);
  inline zssmatrix& operator-=(const zssmatrix&);
  inline zssmatrix& operator*=(const zssmatrix&);
  //// operators with _zssmatrix ////
  inline zssmatrix& operator=(const _zssmatrix&);
  inline zssmatrix& operator+=(const _zssmatrix&);
  inline zssmatrix& operator-=(const _zssmatrix&);
  inline zssmatrix& operator*=(const _zssmatrix&);
  //// operators with double ////
  inline zssmatrix& operator*=(const double&);
  inline zssmatrix& operator/=(const double&);
  //// operators with std::complex<double> ////
  inline zssmatrix& operator*=(const std::complex<double>&);
  inline zssmatrix& operator/=(const std::complex<double>&);

  //// + ////
  inline friend _zgematrix operator+(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const _zgematrix&);
  inline friend _zgematrix operator+(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const _zgematrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator+(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const _zgbmatrix&);
  inline friend _zgematrix operator+(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const _zgbmatrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator+(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator+(const  zssmatrix&, const _zhematrix&);
  inline friend _zgematrix operator+(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator+(const _zhematrix&, const  zssmatrix&);
  
  inline friend _zssmatrix operator+(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator+(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator+(const _zssmatrix&, const  zssmatrix&);
  
  //// - ////
  inline friend _zgematrix operator-(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const _zgematrix&);
  inline friend _zgematrix operator-(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const _zgematrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator-(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const _zgbmatrix&);
  inline friend _zgematrix operator-(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const _zgbmatrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator-(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator-(const  zssmatrix&, const _zhematrix&);
  inline friend _zgematrix operator-(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator-(const _zhematrix&, const  zssmatrix&);
  
  inline friend _zssmatrix operator-(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator-(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator-(const _zssmatrix&, const  zssmatrix&);
  
  //// * ////
  inline friend _zgematrix operator*(const  zssmatrix&, const  zgematrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const _zgematrix&);  
  inline friend _zgematrix operator*(const  zgematrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const _zgematrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator*(const  zssmatrix&, const  zgbmatrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const _zgbmatrix&);  
  inline friend _zgematrix operator*(const  zgbmatrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const _zgbmatrix&, const  zssmatrix&);
  
  inline friend _zgematrix operator*(const  zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const _zhematrix&, const  zssmatrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const  zhematrix&);
  inline friend _zgematrix operator*(const  zssmatrix&, const _zhematrix&);

  inline friend _zssmatrix operator*(const  zssmatrix&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const  zssmatrix&, const _zssmatrix&);
  inline friend _zssmatrix operator*(const _zssmatrix&, const  zssmatrix&);
  
  inline friend _zcovector operator*(const  zssmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zssmatrix&, const _zcovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const  zssmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zssmatrix&);
  
  inline friend _zssmatrix operator*(const  zssmatrix&, const     double&);
  inline friend _zssmatrix operator*(const     double&, const  zssmatrix&);
  inline friend _zssmatrix operator*(const  zssmatrix&, const std::complex<double>&);
  inline friend _zssmatrix operator*(const std::complex<double>&, const  zssmatrix&);
  
  //// / ////
  inline friend _zssmatrix operator/(const  zssmatrix&, const     double&);
  inline friend _zssmatrix operator/(const  zssmatrix&, const  std::complex<double>&);

  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class _zssmatrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
