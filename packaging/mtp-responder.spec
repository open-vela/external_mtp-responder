ExclusiveArch: %arm aarch64
%if "%{?tizen_profile_name}" == "tv"
ExcludeArch: %arm aarch64
%endif

Name:       mtp-responder
Summary:    Media Transfer Protocol daemon (responder)
Version:    0.0.33
Release:    1
Group:      Network & Connectivity/Other
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: %{name}.manifest
BuildRequires: cmake
BuildRequires: libgcrypt-devel
BuildRequires: pkgconfig(capi-content-media-content)
BuildRequires: pkgconfig(capi-media-metadata-extractor)
BuildRequires: pkgconfig(capi-system-info)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(libsystemd)
Buildrequires: pkgconfig(storage)
BuildRequires: pkgconfig(tapi)
BuildRequires: pkgconfig(vconf)
%if 0%{?gtests:1}
BuildRequires:  pkgconfig(gmock)
%endif
%if 0%{?gcov:1}
BuildRequires: lcov
BuildRequires: tar
%endif

%description
This package includes a daemon which processes Media Transper Protocol(MTP) commands as MTP responder role.

%if 0%{?gcov:1}
%package gcov
Summary: Coverage Data of %{name}
Group: Network & Connectivity/Testing

%description gcov
The %{name}-gcov pacakge contains gcov objects
%endif

%prep
%setup -q
cp %{SOURCE1001} .

%build
%if 0%{?gcov:1}
export CFLAGS+=" -fprofile-arcs -ftest-coverage"
export CXXFLAGS+=" -fprofile-arcs -ftest-coverage"
export LDFLAGS+=" -lgcov"
%endif

%cmake . -DCMAKE_VERBOSE_MAKEFILE=OFF \
	-DBIN_INSTALL_DIR:PATH=%{_bindir} \
	-DSYSCONF_DIR:PATH=%{_sysconfdir} \
	-DSYSTEMD_DIR:PATH=%{_unitdir} \
	-DBUILD_GTESTS=%{?gtests:1}%{!?gtests:0} \
	-DBUILD_GCOV=%{?gcov:1}%{!?gcov:0}
make %{?_smp_mflags}

%install
%make_install

%if 0%{?gcov:1}
find .. -name '*.gcno' | tar cf %{name}-gcov.tar -T -
install -d -m 755 %{buildroot}%{_datadir}/gcov/obj
tar xf %{name}-gcov.tar -C %{buildroot}%{_datadir}/gcov/obj
%endif

%files
%manifest %{name}.manifest
%{_bindir}/%{name}
%{_unitdir}/%{name}.service
%{_unitdir}/%{name}.socket
%{_prefix}/lib/udev/rules.d/99-%{name}.rules
/opt/var/lib/misc/%{name}.conf
%{_sysconfdir}/%{name}/descs
%{_sysconfdir}/%{name}/strs
%if 0%{?gtests:1}
%{_bindir}/gtest*
%endif
%license LICENSE.APLv2

%if 0%{?gcov:1}
%files gcov
%{_datadir}/gcov/*
%endif

