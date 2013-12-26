//=============================================================================
//! Real Double-precision Symmetric Matrix Class [L-type (UPLO=L) Strage]
class dsymatrix
{
private:
  //// objects ////
  long N; //!< matrix column size or row size (NOT accessible)
  double* Array; //!< 1D array to store matrix data (NOT accessible)
  double** Darray; //!< array of pointers of column head addresses(NOT accessible)
  
public:
  //// const references ////
  long const& n; //!< matrix column size or row size (readable)
  double* const& array; //!< 1D array to store matrix data (readable)
  double** const& darray; //!< array of pointers of column head addresses (readable)
  
  //// constructor ////
  inline dsymatrix();
  inline dsymatrix(const dsymatrix&);
  inline dsymatrix(const _dsymatrix&);
  inline dsymatrix(const dgbmatrix&);
  inline dsymatrix(const _dgbmatrix&);
  inline dsymatrix(const long&);
  inline dsymatrix(const char*);
  inline ~dsymatrix(); //destructor
  
  //// cast ////
  inline operator _zhematrix();
  
  //// io ////
  inline double& operator()(const long&, const long&);
  inline double operator()(const long&, const long&) const;
  inline void set(const long&, const long&, const double&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dsymatrix&);
  inline void write(const char*) const;
  inline void read(const char*);
  
  //// misc ////
  inline void complete() const;
  inline void clear();
  inline void zero();
  inline void identity();
  inline void chsign();
  inline void copy(const dsymatrix&);
  inline void shallow_copy(const _dsymatrix&);
  inline void resize(const long&);
  inline friend void swap(dsymatrix&, dsymatrix&);
  inline friend _dsymatrix _(dsymatrix&);
  
  //// calc ////
  inline friend _dsymatrix t(const dsymatrix&);
  inline friend _dgematrix i(const dsymatrix&);
  
  //// lapack ////
  inline long dsysv(dgematrix&);
  inline long dsysv(dcovector&);
  inline long dsyev(std::vector<double>&, const bool&);
  inline long dsyev(std::vector<double>&, std::vector<dcovector>&);
  inline long dsyev(std::vector<double>&, std::vector<drovector>&);
  inline long dsygv(dsymatrix&, std::vector<double>&);
  inline long dsygv(dsymatrix&, std::vector<double>&, std::vector<dcovector>&);
  
  //// unary ////
  inline friend const dsymatrix& operator+(const dsymatrix&);
  inline friend _dsymatrix operator-(const dsymatrix&);
  
  //// operators with dsymatrix ////
  inline dsymatrix& operator=(const dsymatrix&);
  inline dsymatrix& operator+=(const dsymatrix&);
  inline dsymatrix& operator-=(const dsymatrix&);
  inline dsymatrix& operator*=(const dsymatrix&);
  //// operators with _dsymatrix ////
  inline dsymatrix& operator=(const _dsymatrix&);
  inline dsymatrix& operator+=(const _dsymatrix&);
  inline dsymatrix& operator-=(const _dsymatrix&);
  inline dsymatrix& operator*=(const _dsymatrix&);
  
  //// operators with double ////
  inline dsymatrix& operator*=(const double&);
  inline dsymatrix& operator/=(const double&);
  
  //// + ////
  inline friend _dsymatrix operator+(const  dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator+(const  dsymatrix&, const _dsymatrix&);
  inline friend _dsymatrix operator+(const _dsymatrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator+(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator+(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dsymatrix&);

  inline friend _dgematrix operator+(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const  dsymatrix&);
  
  //// - ////
  inline friend _dsymatrix operator-(const  dsymatrix&, const  dsymatrix&);
  inline friend _dsymatrix operator-(const  dsymatrix&, const _dsymatrix&);
  inline friend _dsymatrix operator-(const _dsymatrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator-(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator-(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dsymatrix&);

  inline friend _dgematrix operator-(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const  dsymatrix&);
  
  //// * ////
  inline friend _dgematrix operator*(const _dsymatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator*(const  dsymatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dsymatrix&);
  
  inline friend _dgematrix operator*(const  dsymatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const  dsymatrix&);

  inline friend _dgematrix operator*(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const  dsymatrix&);
  
  inline friend _dcovector operator*(const  dsymatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dsymatrix&, const _dcovector&);
  
  inline friend _drovector operator*(const  drovector&, const  dsymatrix&);
  inline friend _drovector operator*(const _drovector&, const  dsymatrix&);
  
  inline friend _dsymatrix operator*(const  dsymatrix&, const     double&);
  inline friend _dsymatrix operator*(const     double&, const  dsymatrix&);

  //// / ////
  inline friend _dsymatrix operator/(const  dsymatrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class _dsymatrix;
  friend class  dssmatrix;
  friend class _dssmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
