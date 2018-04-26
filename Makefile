all:
	gcc *.c -shared -o my_malloc.so libft/libft.a
	launchctl setenv DYLB_LIBRARY_PATH .
	launchctl setenv DYLB_INSERT_LIBRARIES my_malloc.so
	launchctl setenv DYLB_FORCE_FLAT_NAMESPACE 1