# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 17:53:33 by brabo-hi          #+#    #+#              #
#    Updated: 2018/05/07 17:53:34 by brabo-hi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc *.c -shared -o my_malloc.so libft/libft.a
	launchctl setenv DYLB_LIBRARY_PATH .
	launchctl setenv DYLB_INSERT_LIBRARIES my_malloc.so
	launchctl setenv DYLB_FORCE_FLAT_NAMESPACE 1