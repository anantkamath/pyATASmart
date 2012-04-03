from distutils.core import setup, Extension
 
pyATASmart = Extension('pyATASmart', 
			sources = ['pyATASmart.c'],
                        include_dirs = ['/usr/local/include'],
                        libraries = ['atasmart'],
                        library_dirs = ['/usr/local/lib'])
 
setup (name = 'pyATASmart',
       version = '0.1',
       author='Anant Kamath',
       author_email='kamathanant@gmail.com',
       url='http://www.github.com/anantkamath/pyATASmart',

       description = 'Python bindings for the libatasmart library',
       ext_modules = [pyATASmart])