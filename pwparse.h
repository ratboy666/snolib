struct passwd {name, password, uid, gid, gecos, dir, shell}

procedure pwparse (a) n, p, u, g, ge, d, s {
	if (a ? fence &&
	    break(":") . n && len(1) &&
	    break(":") . p && len(1) &&
	    break(":") . u && len(1) &&
	    break(":") . g && len(1) &&
	    break(":") . ge && len(1) &&
	    break(":") . d && len(1) &&
	    rem . s)
		return passwd(n,p,u,g,ge,d,s)
	freturn
}
