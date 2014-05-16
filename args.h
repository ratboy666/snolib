# make arguments available in the style of C programs, including
# argc, argv, and getenv.  Difference: argv[0] does not appear.

argc = host (3)
argv = table()
while (argv[argc - host(3) + 1] = host (2, argc))
	argc = argc + 1
argc = argc - host(3) + 1

procedure getenv (name) {
	if (getenv = host (4, name))
		return
	else
		freturn
}
