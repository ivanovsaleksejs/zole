{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "zole";

  src = ./.;

  buildInputs = [
    pkgs.gcc
    pkgs.fcgi
    pkgs.libwebsockets
    pkgs.openssl
    pkgs.spawn_fcgi
    pkgs.hiredis
    pkgs.cjson
  ];

  buildPhase = ''
    make all
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp zole $out/bin/
  '';

  cleanPhase = ''
    make clean
  '';

  meta = {
    description = "A Zole game server in C";
    license = pkgs.lib.licenses.gpl3Plus;
    maintainers = with pkgs.lib.maintainers; [ ivanovsaleksejs ];
  };
}
