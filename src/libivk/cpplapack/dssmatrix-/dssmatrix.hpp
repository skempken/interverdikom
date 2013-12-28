//=============================================================================
//! Real Double-precision Sparse Matrix Class
class dssmatrix
{
private:
  //// objects ////
  long M; //!< matrix row size (NOT accessible)
  long N; //!< matrix column size (NOT accessible)
  long CAP; //!< the length of data arrays (NOT accessible)
  long VOL; //!< the number of non-zero components (NOT accessible)
  double* Array; //!< 1D array to store non-zero matrix data (NOT accessible)
  long* Indx; //!< 1D array to store the i-index of non-zero matrix components (NOT accessible)
  long* Jndx; //!< 1D array to store the j-index of non-zero matrix components (NOT accessible)
  
public:
  //// const references ////
  long const& m; //!< matrix row size (readable)
  long const& n; //!< matrix column size (readable)
  long const& cap; //!<  the length of data arrays (readable)
  long const& vol; //!< the number of non-zero components (readable)
  double* const& array; //!< 1D array to store matrix data (readable)
  long* const& indx; //!< 1D array to store the i-index of non-zero matrix components (readable)
  long* const& jndx; //!< 1D array to store the j-index of non-zero matrix components (readable)
  
  //// constructor ////
  inline dssmatrix();
  inline dssmatrix(const dssmatrix&);
  inline dssmatrix(const _dssmatrix&);
  inline dssmatrix(const long&, const long&, const long&);
  inline dssmatrix(const char*);
  inline ~dssmatrix(); //destructor
  
  //// cast ////
  inline operator _zssmatrix();
  
  //// io ////
  inline double operator()(const long&, const long&) const;
  inline void put(const long&, const long&, const double&);
  inline void fput(const long&, const long&, const double&);
  inline void add(const long&, const long&, const double&);
  inline void sub(const long&, const long&, const double&);
  inline void mult(const long&, const long&, const double&);
  inline void div(const long&, const long&, const double&);
  inline void del(const long&, const long&);
  inline void fdel(const long&);
  inline friend std::ostream& operator<<(std::ostream&, const dssmatrix&);
  inline void write(const char *) const;
  inline void read(const char *);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const dssmatrix&);
  inline void shallow_copy(const _dssmatrix&);
  inline void resize(const long&, const long&, const long&);
  inline void expand(const long&);
  inline bool isListed(const long&, const long&);
  inline long number(const long&, const long&);
  inline void checkup();
  inline friend void swap(dssmatrix&, dssmatrix&);
  inline friend _dssmatrix _(dssmatrix&);
  
  //// calc ////
  inline friend _dssmatrix t(const dssmatrix&);
  inline friend void idamax(long&, long&, const dssmatrix&);
  inline friend double damax(const dssmatrix&);
  
  //// unary ////
  inline friend const dssmatrix& operator+(const dssmatrix&);
  inline friend _dssmatrix operator-(const dssmatrix&);
  
  //// operators with dssmatrix ////
  inline dssmatrix& operator=(const dssmatrix&);
  inline dssmatrix& operator+=(const dssmatrix&);
  inline dssmatrix& operator-=(const dssmatrix&);
  inline dssmatrix& operator*=(const dssmatrix&);
  
  //// operators with _dssmatrix ////
  inline dssmatrix& operator=(const _dssmatrix&);
  inline dssmatrix& operator+=(const _dssmatrix&);
  inline dssmatrix& operator-=(const _dssmatrix&);
  inline dssmatrix& operator*=(const _dssmatrix&);

  //// operators with double ////
  inline dssmatrix& operator*=(const double&);
  inline dssmatrix& operator/=(const double&);

  //// + ////
  inline friend _dgematrix operator+(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator+(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator+(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const  dssmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const  dssmatrix&);
  
  inline friend _dssmatrix operator+(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator+(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator+(const _dssmatrix&, const  dssmatrix&);
  
  //// - ////
  inline friend _dgematrix operator-(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator-(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator-(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const  dssmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator-(const _dsymatrix&, const  dssmatrix&);
  
  inline friend _dssmatrix operator-(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator-(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator-(const _dssmatrix&, const  dssmatrix&);
  
  //// * ////
  inline friend _dgematrix operator*(const  dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const _dgematrix&);  
  inline friend _dgematrix operator*(const  dgematrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator*(const  dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const _dgbmatrix&);  
  inline friend _dgematrix operator*(const  dgbmatrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const  dssmatrix&);
  
  inline friend _dgematrix operator*(const  dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const  dssmatrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const  dssmatrix&, const _dsymatrix&);

  inline friend _dssmatrix operator*(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator*(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator*(const _dssmatrix&, const  dssmatrix&);
  
  inline friend _dcovector operator*(const  dssmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dssmatrix&, const _dcovector&);
  
  inline friend _drovector operator*(const  drovector&, const  dssmatrix&);
  inline friend _drovector operator*(const _drovector&, const  dssmatrix&);
  
  inline friend _dssmatrix operator*(const  dssmatrix&, const     double&);
  inline friend _dssmatrix operator*(const     double&, const  dssmatrix&);
  
  //// / ////
  inline friend _dssmatrix operator/(const  dssmatrix&, const     double&);

  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class _dssmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
