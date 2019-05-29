//Maya ASCII 2016 scene
//Name: PCgenjin_enemy.ma
//Last modified: Thu, May 09, 2019 09:52:18 AM
//Codeset: 932
requires maya "2016";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2016";
fileInfo "version" "2016";
fileInfo "cutIdentifier" "201502261600-953408";
fileInfo "osv" "Microsoft Windows 8 Home Premium Edition, 64-bit  (Build 9200)\n";
fileInfo "license" "education";
createNode transform -s -n "persp";
	rename -uid "85657C75-4AD9-0331-C147-8C88B917D225";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 5.0054518713558949 19.64850965524726 36.252336532305186 ;
	setAttr ".r" -type "double3" -21.338352728863423 7.8000000000000922 2.0064103041282324e-016 ;
	setAttr ".rp" -type "double3" 0 8.8817841970012523e-016 0 ;
	setAttr ".rpt" -type "double3" 1.4855422871726926e-017 -7.521085041029052e-018 1.1438042028009302e-016 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "4F57D188-4A0D-7E74-941C-F3A0E89C3B42";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999979;
	setAttr ".coi" 38.287645943619523;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 2.8417056177951925 5.2937189174172001 -0.14617404688954139 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "E522F91D-4903-094F-2F46-86A94FB45A54";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 100.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "D8969AAA-4EBE-2106-A9A3-DAB753AEF72F";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	rename -uid "AF6C8C19-481C-EBBC-64A7-BE8BCCA852A5";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 2.571428571428573 4.8074534161490678 100.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "CD21616E-4780-2BC0-51D8-35A18D99E4E0";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	rename -uid "6BCAE491-4DC4-EE98-65B0-57A155145B19";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 100.1 6.832142831669862 0.42146694328129264 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "4CBE488B-4D8E-DE18-919F-1FA8DCD27CEF";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 37.780354809947447;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pCylinder1";
	rename -uid "695250EE-4800-2A1A-F692-3489D56A82D1";
	setAttr ".t" -type "double3" 0.017236900811484546 3.6782743810806422 1.7316199646817632 ;
	setAttr ".s" -type "double3" 3 3 3 ;
createNode mesh -n "pCylinderShape1" -p "pCylinder1";
	rename -uid "B8806813-4B30-CCEC-AA2D-269792A74654";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.49048977345228195 0.49999992549419403 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 162 ".pt[0:161]" -type "float3"  -0.13922417 0.74040824 1.1793232 
		-0.11843082 0.69981116 1.1923395 -0.086045101 0.66759545 1.2026716 -0.045236565 0.64691037 
		1.2093048 -2.0632667e-008 0.63978243 1.2115909 0.045236554 0.64691037 1.2093048 0.086045012 
		0.66759557 1.2026719 0.11843082 0.69981128 1.1923395 0.13922386 0.74040824 1.1793232 
		0.14638852 0.78540921 1.1648921 0.13922386 0.83041048 1.1504624 0.11843082 0.87100494 
		1.1374439 0.086045004 0.90322328 1.1271136 0.045236554 0.92390859 1.1204802 -1.626997e-008 
		0.93103546 1.1181941 -0.045236565 0.92390859 1.1204802 -0.086045027 0.90322328 1.1271135 
		-0.11843082 0.87100506 1.1374439 -0.13922386 0.83041072 1.1504624 -0.14638852 0.78540921 
		1.1648921 -0.39952767 -1.2079252 -0.25970468 -0.33985892 -1.2063394 -0.14260809 -0.24692184 
		-1.205079 -0.049679801 -0.12981451 -1.2042716 0.0099840462 -5.0078427e-008 -1.2039942 
		0.030542187 0.12981445 -1.2042716 0.0099840462 0.24692178 -1.2050792 -0.049679939 
		0.33985868 -1.2063392 -0.14260806 0.39952746 -1.2079252 -0.25970471 0.42008832 -1.2096819 
		-0.38950744 0.39952746 -1.2114395 -0.51930994 0.33985868 -1.213026 -0.63640624 0.24692167 
		-1.2142828 -0.72933412 0.1298144 -1.2150893 -0.78899825 -3.7558799e-008 -1.2153704 
		-0.80955613 -0.12981448 -1.2150893 -0.78899825 -0.24692178 -1.2142828 -0.72933412 
		-0.33985868 -1.213026 -0.63640624 -0.39952746 -1.2114395 -0.51930994 -0.42008832 
		-1.2096819 -0.38950744 -2.0632667e-008 0.66087973 2.0209448 -5.0078427e-008 -1.2096819 
		-0.38950744 -0.40652505 0.30823362 -0.063405253 -0.34581107 0.20911638 0.0027371827 
		-0.25124654 0.13045612 0.055228166 -0.13208804 0.079953492 0.088929288 -2.5477734e-008 
		0.062551476 0.10054171 0.13208792 0.079953507 0.088929266 0.25124618 0.13045628 0.055228103 
		0.34581095 0.20911638 0.0027371254 0.40652502 0.30823374 -0.063405275 0.42744544 
		0.41810617 -0.13672462 0.40652499 0.52797836 -0.210044 0.34581095 0.62709594 -0.27618632 
		0.25124606 0.70575672 -0.32867759 0.13208787 0.75625938 -0.36237845 -8.917209e-008 
		0.77366114 -0.3739908 -0.13208793 0.75625932 -0.36237842 -0.25124618 0.70575672 -0.32867759 
		-0.34581098 0.62709594 -0.27618632 -0.40652502 0.52797842 -0.21004403 -0.42744544 
		0.41810617 -0.13672459 -0.30899495 -0.90350181 -0.33380029 -0.26284698 -0.90185976 
		-0.24778943 -0.19096939 -0.90056664 -0.18008062 -0.10039856 -0.89974248 -0.13691656 
		-2.5575256e-008 -0.899459 -0.12210654 0.10039844 -0.89974248 -0.13691656 0.19096933 
		-0.9005664 -0.18008082 0.26284674 -0.90185976 -0.24778955 0.30899468 -0.90350181 
		-0.33380029 0.3248961 -0.90533727 -0.42987055 0.30899468 -0.90718335 -0.52655303 
		0.26284674 -0.90885705 -0.61419761 0.19096923 -0.91019011 -0.68399167 0.10039838 
		-0.9110471 -0.72890025 -4.4949438e-008 -0.91134173 -0.74439228 -0.10039848 -0.9110471 
		-0.72890019 -0.19096933 -0.91019011 -0.68399143 -0.26284677 -0.90885729 -0.61419755 
		-0.30899468 -0.90718335 -0.52655303 -0.3248961 -0.9053371 -0.42987052 -0.26944605 
		-0.65930969 -0.34066698 -0.22920458 -0.66027981 -0.2662223 -0.16652682 -0.66104275 
		-0.20752262 -0.087548293 -0.66153139 -0.17004225 -2.0872315e-008 -0.66169852 -0.15716904 
		0.087548196 -0.66153139 -0.17004228 0.16652676 -0.66104275 -0.20752273 0.2292044 
		-0.66027981 -0.26622233 0.26944578 -0.65930969 -0.34066698 0.28331193 -0.65823025 
		-0.42371058 0.26944578 -0.65714252 -0.50720876 0.2292044 -0.65615845 -0.58286238 
		0.16652666 -0.65537572 -0.64309448 0.087548189 -0.65487063 -0.68184644 -4.3489653e-008 
		-0.65469724 -0.69521219 -0.087548204 -0.65487069 -0.68184668 -0.16652676 -0.65537572 
		-0.64309448 -0.2292044 -0.65615845 -0.58286238 -0.26944578 -0.65714228 -0.50720882 
		-0.28331193 -0.65823025 -0.42371058 -0.23906569 -0.31642169 -0.28462398 -0.20336151 
		-0.32598272 -0.21978371 -0.14775074 -0.33353457 -0.16857043 -0.077677093 -0.33836341 
		-0.13581608 -1.7212265e-008 -0.34002456 -0.12455428 0.077677049 -0.33836341 -0.13581608 
		0.14775068 -0.33353457 -0.16857049 0.20336133 -0.32598272 -0.21978371 0.23906542 
		-0.31642169 -0.28462398 0.25136819 -0.3057712 -0.35685587 0.23906542 -0.29507187 
		-0.42941755 0.20336133 -0.28538278 -0.4951283 0.14775057 -0.27767062 -0.54743075 
		0.077677034 -0.27270922 -0.58107722 -4.2490367e-008 -0.270998 -0.59268242 -0.077677056 
		-0.27270922 -0.58107722 -0.14775068 -0.27767062 -0.54743075 -0.20336133 -0.28538302 
		-0.4951283 -0.23906542 -0.29507187 -0.42941755 -0.25136819 -0.3057712 -0.35685587 
		-0.23906569 0.049035404 -0.17005493 -0.20336151 0.025553962 -0.10941701 -0.14775074 
		0.0069754664 -0.061440464 -0.077677101 -0.0049266843 -0.030704752 -1.5904826e-008 
		-0.0090232538 -0.020125706 0.077677049 -0.0049266247 -0.030704752 0.14775068 0.0069754664 
		-0.061440568 0.20336133 0.025553962 -0.10941702 0.23906542 0.049035478 -0.17005496 
		0.25136819 0.075157635 -0.23751196 0.23906542 0.1013749 -0.30521435 0.20336133 0.1251041 
		-0.3664923 0.14775057 0.14398645 -0.41525394 0.077677034 0.15613255 -0.44661951 -4.6400434e-008 
		0.16032155 -0.45743746 -0.077677056 0.15613255 -0.44661948 -0.14775068 0.14398645 
		-0.41525394 -0.20336133 0.1251041 -0.3664923 -0.23906542 0.1013749 -0.30521452 -0.25136819 
		0.075157635 -0.23751196 -0.25862163 0.50132561 0.56767017 -0.22170831 0.43556145 
		0.60537094 -0.16218095 0.3825807 0.63574332 -0.085667238 0.3481403 0.65548748 -2.5546141e-008 
		0.33618817 0.66233903 0.085667141 0.3481403 0.65548748 0.16218083 0.3825807 0.63574356 
		0.2217081 0.43556139 0.60537094 0.25862148 0.50132561 0.56767017 0.26985255 0.57313359 
		0.52650458 0.25489232 0.64398062 0.48589092 0.21561728 0.70719594 0.4496513 0.15601724 
		0.75695831 0.42112359 0.081820689 0.78873849 0.40290475 -4.7772094e-008 0.79966092 
		0.3966437 -0.081820704 0.78873849 0.40290475 -0.15601726 0.75695831 0.42112359 -0.21561728 
		0.70719594 0.44965127 -0.25489238 0.64398068 0.48589081 -0.26985255 0.57313347 0.52650458;
	setAttr ".bw" 3;
createNode transform -n "group";
	rename -uid "AEDB9672-423A-414C-B5C8-BA83E78BBB7A";
	setAttr ".t" -type "double3" 0 0.84827942593920769 4.1298663371764697 ;
	setAttr ".rp" -type "double3" -1.1920928955078125e-007 0 -2.0548075289185297 ;
	setAttr ".sp" -type "double3" -1.1920928955078125e-007 0 -2.0548075289185297 ;
createNode transform -n "group1";
	rename -uid "B358A21D-460F-DAB6-BC82-EF9C709AFFCD";
	setAttr ".t" -type "double3" 0 2.706657131095159 -2.0349209844853022 ;
	setAttr ".rp" -type "double3" -1.1920928955078125e-007 0 2.07505880825794 ;
	setAttr ".sp" -type "double3" -1.1920928955078125e-007 0 2.07505880825794 ;
createNode transform -n "pasted__group" -p "group1";
	rename -uid "8E1A12EC-46CF-10A3-DB5A-94AFE1C4D805";
	setAttr ".t" -type "double3" 0 0 4.1298663371764697 ;
	setAttr ".rp" -type "double3" -1.1920928955078125e-007 0 -2.0548075289185297 ;
	setAttr ".sp" -type "double3" -1.1920928955078125e-007 0 -2.0548075289185297 ;
createNode transform -n "group2";
	rename -uid "6874968F-4160-6F6A-2195-9EB958083AEF";
	setAttr ".t" -type "double3" 0 0.84827942593920769 -1.9648631003679027 ;
	setAttr ".rp" -type "double3" -4.219570254315741e-008 -1.4045958571365014 0.89109034869489989 ;
	setAttr ".sp" -type "double3" -4.219570254315741e-008 -1.4045958571365014 0.89109034869489989 ;
createNode transform -n "group3";
	rename -uid "1B574C99-4E66-B1A2-8BA9-D3A97DD37A11";
	setAttr ".t" -type "double3" 0 0.84827942593920769 -2.0061233275057759 ;
	setAttr ".rp" -type "double3" -5.7545870152386769e-008 0.4479692867245908 1.0999999136811949 ;
	setAttr ".sp" -type "double3" -5.7545870152386769e-008 0.4479692867245908 1.0999999136811949 ;
createNode transform -n "pSphere1";
	rename -uid "34F0FBFD-4391-B521-3E0B-FD9E87FA2A0F";
	setAttr ".t" -type "double3" -1.7827630991885117 0.8 1 ;
	setAttr ".r" -type "double3" 0 -20 0 ;
	setAttr ".s" -type "double3" 1 0.84179579400760707 1.6208452677004868 ;
createNode mesh -n "pSphereShape1" -p "pSphere1";
	rename -uid "F36FB022-47EE-7F7B-00FE-9FAE466AA6EC";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.15041666477918625 0.84958338737487793 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bw" 3;
createNode transform -n "pSphere2";
	rename -uid "441FE3E8-4D9E-B1C0-297B-A4BFBC32B310";
	setAttr ".t" -type "double3" 1.8172369008114844 0.8 1 ;
	setAttr ".r" -type "double3" 0 20 0 ;
	setAttr ".s" -type "double3" 1 0.84179579400760707 1.6208452677004868 ;
createNode mesh -n "pSphereShape2" -p "pSphere2";
	rename -uid "377D310B-41F7-FD29-C0E5-399BC50350FA";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bw" 3;
createNode transform -n "pSphere4";
	rename -uid "573C3B0B-42A7-6DE6-4424-3C8E493A09A4";
	setAttr ".t" -type "double3" 0.017236900811484546 6.3893663759060058 0.23652744971959594 ;
createNode mesh -n "pSphereShape3" -p "pSphere4";
	rename -uid "01630C0A-4B70-732B-CBEB-B7BA8CADE263";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.30879434198141098 0.27527262270450592 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 85 ".pt";
	setAttr ".pt[0]" -type "float3" 0.36252725 0.88437498 -0.17458387 ;
	setAttr ".pt[1]" -type "float3" 0.25087667 0.88437498 -0.3145895 ;
	setAttr ".pt[2]" -type "float3" 0.089536846 0.88437498 -0.39228681 ;
	setAttr ".pt[3]" -type "float3" -0.089536838 0.88437498 -0.39228684 ;
	setAttr ".pt[4]" -type "float3" -0.25087667 0.88437498 -0.31458962 ;
	setAttr ".pt[5]" -type "float3" -0.36252725 0.88437498 -0.17458406 ;
	setAttr ".pt[6]" -type "float3" -0.4023751 0.88437498 -1.1130894e-007 ;
	setAttr ".pt[7]" -type "float3" -0.36252731 0.88437498 0.17458379 ;
	setAttr ".pt[8]" -type "float3" -0.2508769 0.88437498 0.31458944 ;
	setAttr ".pt[9]" -type "float3" -0.089537047 0.88437498 0.39228672 ;
	setAttr ".pt[10]" -type "float3" 0.089536779 0.88437498 0.39228675 ;
	setAttr ".pt[11]" -type "float3" 0.25087658 0.88437498 0.3145895 ;
	setAttr ".pt[12]" -type "float3" 0.36252725 0.88437498 0.1745839 ;
	setAttr ".pt[13]" -type "float3" 0.40237507 0.88437498 -3.935871e-008 ;
	setAttr ".pt[14]" -type "float3" 0.7068764 0.66308475 -0.34041345 ;
	setAttr ".pt[15]" -type "float3" 0.48917356 0.66308475 -0.61340421 ;
	setAttr ".pt[16]" -type "float3" 0.17458394 0.66308475 -0.76490241 ;
	setAttr ".pt[17]" -type "float3" -0.17458384 0.66308475 -0.76490247 ;
	setAttr ".pt[18]" -type "float3" -0.48917332 0.66308475 -0.61340445 ;
	setAttr ".pt[19]" -type "float3" -0.7068764 0.66308475 -0.34041393 ;
	setAttr ".pt[20]" -type "float3" -0.78457367 0.66308475 -1.7965132e-007 ;
	setAttr ".pt[21]" -type "float3" -0.7068764 0.66308475 0.34041339 ;
	setAttr ".pt[22]" -type "float3" -0.48917368 0.66308475 0.61340421 ;
	setAttr ".pt[23]" -type "float3" -0.17458408 0.66308475 0.76490229 ;
	setAttr ".pt[24]" -type "float3" 0.17458378 0.66308475 0.76490241 ;
	setAttr ".pt[25]" -type "float3" 0.48917332 0.66308475 0.61340421 ;
	setAttr ".pt[26]" -type "float3" 0.7068764 0.66308475 0.3404139 ;
	setAttr ".pt[27]" -type "float3" 0.78457361 0.66308475 -3.935871e-008 ;
	setAttr ".pt[28]" -type "float3" 1.015779 0.26591679 -0.48917326 ;
	setAttr ".pt[29]" -type "float3" 0.70294082 -0.17596039 -0.88146031 ;
	setAttr ".pt[30]" -type "float3" 0.25087696 0.26591679 -1.0991631 ;
	setAttr ".pt[31]" -type "float3" -0.25087649 -0.17596039 -1.0991629 ;
	setAttr ".pt[32]" -type "float3" -0.70294076 0.26591679 -0.88146043 ;
	setAttr ".pt[33]" -type "float3" -1.0157789 -0.17596039 -0.4891738 ;
	setAttr ".pt[34]" -type "float3" -1.1274292 0.26591679 -2.4095885e-007 ;
	setAttr ".pt[35]" -type "float3" -1.0157795 -0.17596039 0.48917332 ;
	setAttr ".pt[36]" -type "float3" -0.70294112 0.26591679 0.88146031 ;
	setAttr ".pt[37]" -type "float3" -0.25087699 -0.17596039 1.0991628 ;
	setAttr ".pt[38]" -type "float3" 0.25087649 0.26591679 1.0991629 ;
	setAttr ".pt[39]" -type "float3" 0.70294082 -0.17596039 0.88146043 ;
	setAttr ".pt[40]" -type "float3" 1.015779 0.26591679 0.48917356 ;
	setAttr ".pt[41]" -type "float3" 1.1274292 -0.17596039 -3.935871e-008 ;
	setAttr ".pt[42]" -type "float3" 0.58495694 0.029850334 -0.28170019 ;
	setAttr ".pt[43]" -type "float3" 0.40480289 0.029850334 -0.50760633 ;
	setAttr ".pt[44]" -type "float3" 0.14447255 0.029850334 -0.63297516 ;
	setAttr ".pt[45]" -type "float3" -0.14447227 0.029850326 -0.63297516 ;
	setAttr ".pt[46]" -type "float3" -0.40480262 0.029850326 -0.50760645 ;
	setAttr ".pt[47]" -type "float3" -0.58495688 0.029850326 -0.28170061 ;
	setAttr ".pt[48]" -type "float3" -0.64925325 0.029850326 -1.3602646e-007 ;
	setAttr ".pt[49]" -type "float3" -0.584957 0.029850326 0.28170019 ;
	setAttr ".pt[50]" -type "float3" -0.40480289 0.029850326 0.50760633 ;
	setAttr ".pt[51]" -type "float3" -0.14447257 0.029850326 0.63297516 ;
	setAttr ".pt[52]" -type "float3" 0.14447229 0.029850334 0.63297516 ;
	setAttr ".pt[53]" -type "float3" 0.40480265 0.029850334 0.50760639 ;
	setAttr ".pt[54]" -type "float3" 0.58495694 0.029850334 0.28170049 ;
	setAttr ".pt[55]" -type "float3" 0.64925325 0.029850334 -1.9930944e-008 ;
	setAttr ".pt[56]" -type "float3" 0.2669403 0.052486718 -0.12855156 ;
	setAttr ".pt[57]" -type "float3" 0.18472846 0.052486718 -0.23164202 ;
	setAttr ".pt[58]" -type "float3" 0.065928832 0.052486718 -0.28885293 ;
	setAttr ".pt[59]" -type "float3" -0.065928757 0.052486718 -0.28885293 ;
	setAttr ".pt[60]" -type "float3" -0.18472835 0.052486718 -0.23164208 ;
	setAttr ".pt[61]" -type "float3" -0.26694021 0.052486718 -0.12855168 ;
	setAttr ".pt[62]" -type "float3" -0.29628122 0.052486718 -5.2979246e-008 ;
	setAttr ".pt[63]" -type "float3" -0.26694027 0.052486718 0.1285516 ;
	setAttr ".pt[64]" -type "float3" -0.18472849 0.052486718 0.23164208 ;
	setAttr ".pt[65]" -type "float3" -0.065928839 0.052486718 0.28885293 ;
	setAttr ".pt[66]" -type "float3" 0.065928765 0.052486718 0.28885293 ;
	setAttr ".pt[67]" -type "float3" 0.1847284 0.052486718 0.23164208 ;
	setAttr ".pt[68]" -type "float3" 0.26694027 0.052486718 0.12855163 ;
	setAttr ".pt[69]" -type "float3" 0.29628122 0.052486718 0 ;
	setAttr ".pt[70]" -type "float3" 0.059929222 0.020009102 -0.028860377 ;
	setAttr ".pt[71]" -type "float3" 0.041472312 0.020009102 -0.052004617 ;
	setAttr ".pt[72]" -type "float3" 0.014801305 0.020009102 -0.064848706 ;
	setAttr ".pt[73]" -type "float3" -0.014801284 0.020009102 -0.064848706 ;
	setAttr ".pt[74]" -type "float3" -0.041472297 0.020009102 -0.052004635 ;
	setAttr ".pt[75]" -type "float3" -0.059929211 0.020009102 -0.028860401 ;
	setAttr ".pt[76]" -type "float3" -0.066516414 0.020009102 -1.1894064e-008 ;
	setAttr ".pt[77]" -type "float3" -0.059929222 0.020009102 0.028860379 ;
	setAttr ".pt[78]" -type "float3" -0.041472316 0.020009102 0.052004624 ;
	setAttr ".pt[79]" -type "float3" -0.014801307 0.020009102 0.064848706 ;
	setAttr ".pt[80]" -type "float3" 0.014801286 0.020009102 0.064848714 ;
	setAttr ".pt[81]" -type "float3" 0.041472301 0.020009102 0.052004635 ;
	setAttr ".pt[82]" -type "float3" 0.059929222 0.020009102 0.028860396 ;
	setAttr ".pt[83]" -type "float3" 0.066516414 0.020009102 0 ;
	setAttr ".pt[182]" -type "float3" -7.1853712e-008 0.95979619 -3.935871e-008 ;
	setAttr ".bw" 3;
createNode transform -n "pSphere5";
	rename -uid "B5FC6CF8-4337-241F-0013-D3966B3159C0";
	setAttr ".t" -type "double3" 0 0 8.7377396492684145 ;
createNode transform -n "transform1" -p "pSphere5";
	rename -uid "9159CD70-4445-8514-49D5-C29AA1864FA5";
	setAttr ".v" no;
createNode mesh -n "pSphereShape4" -p "transform1";
	rename -uid "68A8FA2C-4248-5D00-920B-17AC083A0C8C";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr -s 2 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "pCylinder2";
	rename -uid "4523DC9E-497D-9EAE-56CF-B4B2831DD002";
	setAttr ".t" -type "double3" 0 1.6803407307932359 8.734384219579459 ;
	setAttr ".s" -type "double3" 0.72508907571090198 1.0033419584027143 0.72508907571090198 ;
createNode transform -n "transform2" -p "pCylinder2";
	rename -uid "F455703A-4A73-98D2-19F4-23AA59B5E470";
	setAttr ".v" no;
createNode mesh -n "pCylinderShape2" -p "transform2";
	rename -uid "C766CC15-4749-A2C0-E87D-60998007C58C";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr -s 2 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.49999998509883881 0.49999996274709702 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 21 ".pt";
	setAttr ".pt[20]" -type "float3" -0.34366724 -0.17193165 0.11166418 ;
	setAttr ".pt[21]" -type "float3" -0.29234087 -0.17193165 0.21239798 ;
	setAttr ".pt[22]" -type "float3" -0.21239807 -0.17193165 0.2923407 ;
	setAttr ".pt[23]" -type "float3" -0.11166427 -0.17193165 0.34366715 ;
	setAttr ".pt[24]" -type "float3" -4.3076618e-008 -0.17193165 0.36135304 ;
	setAttr ".pt[25]" -type "float3" 0.11166421 -0.17193165 0.34366715 ;
	setAttr ".pt[26]" -type "float3" 0.21239795 -0.17193165 0.29234052 ;
	setAttr ".pt[27]" -type "float3" 0.29234052 -0.17193165 0.21239792 ;
	setAttr ".pt[28]" -type "float3" 0.34366712 -0.17193165 0.11166418 ;
	setAttr ".pt[29]" -type "float3" 0.36135292 -0.17193165 -6.4614937e-008 ;
	setAttr ".pt[30]" -type "float3" 0.34366712 -0.17193165 -0.11166427 ;
	setAttr ".pt[31]" -type "float3" 0.2923407 -0.17193165 -0.21239798 ;
	setAttr ".pt[32]" -type "float3" 0.21239792 -0.17193165 -0.2923407 ;
	setAttr ".pt[33]" -type "float3" 0.11166418 -0.17193165 -0.34366715 ;
	setAttr ".pt[34]" -type "float3" -3.2307469e-008 -0.17193165 -0.36135304 ;
	setAttr ".pt[35]" -type "float3" -0.11166421 -0.17193165 -0.34366715 ;
	setAttr ".pt[36]" -type "float3" -0.21239795 -0.17193165 -0.29234064 ;
	setAttr ".pt[37]" -type "float3" -0.29234052 -0.17193165 -0.21239798 ;
	setAttr ".pt[38]" -type "float3" -0.34366712 -0.17193165 -0.11166424 ;
	setAttr ".pt[39]" -type "float3" -0.36135292 -0.17193165 -6.4614937e-008 ;
	setAttr ".pt[41]" -type "float3" -4.3076618e-008 -0.17193165 -6.4614937e-008 ;
createNode transform -n "pSphere6";
	rename -uid "24362783-491B-C527-EB68-DC8474B8641C";
createNode transform -n "transform3" -p "pSphere6";
	rename -uid "0AF8B6EB-43B7-78F7-053F-5E9E8E47A341";
	setAttr ".v" no;
createNode mesh -n "pSphereShape5" -p "transform3";
	rename -uid "20D54250-4365-A07A-0309-BFBFDB071F5B";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr -s 2 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "pCylinder3";
	rename -uid "1382DBCA-46A7-BB45-F0A3-8F8D3C8DFE92";
	setAttr ".t" -type "double3" 0 1.6937014015502485 0 ;
	setAttr ".s" -type "double3" 0.71752747223520663 1.0075650105777239 0.71752747223520663 ;
createNode transform -n "transform4" -p "pCylinder3";
	rename -uid "B449A0FB-4C82-4914-16AF-89818A8CFBAD";
	setAttr ".v" no;
createNode mesh -n "pCylinderShape3" -p "transform4";
	rename -uid "ABE5B5A3-46A2-E140-2968-BF93795A7984";
	setAttr -k off ".v";
	setAttr ".io" yes;
	setAttr -s 2 ".iog[0].og";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "pSphere7";
	rename -uid "D03A74F7-4C61-BD89-58C7-22BFE2359CCD";
	setAttr ".t" -type "double3" 2 2.8 2.3 ;
createNode mesh -n "pSphereShape6" -p "pSphere7";
	rename -uid "2AEA4783-465F-7A5D-1875-C4B26A89FEC7";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.45000004768371582 0.30000001192092896 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bw" 3;
createNode transform -n "pSphere8";
	rename -uid "F70E3086-438A-8F7E-53E2-6BAA84659C65";
	setAttr ".t" -type "double3" -2 2.8 2.3 ;
createNode mesh -n "pSphereShape7" -p "pSphere8";
	rename -uid "AF7BDCBA-4610-F187-CCF6-33976B050B98";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.151491679251194 0.84858983755111694 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".bw" 3;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "0A83ECC8-40C9-B4E7-A705-65A2381542E1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
createNode displayLayerManager -n "layerManager";
	rename -uid "179198FF-4A96-9454-FD42-E483767CB3CE";
createNode displayLayer -n "defaultLayer";
	rename -uid "E7A8BCEC-4979-41A8-84D6-559A6E1F0F85";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "595EC5FC-45F6-9321-1AA9-E3AF11C48241";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "5E73D93D-4E6F-5CE0-2FEB-BAA2E7A23034";
	setAttr ".g" yes;
createNode polyCylinder -n "polyCylinder1";
	rename -uid "3F62DA59-4A5D-5AB5-3A13-0484F70D67D8";
	setAttr ".sc" 1;
	setAttr ".cuv" 3;
createNode polyCut -n "polyCut1";
	rename -uid "7A32B900-49DC-1037-01BD-62984A96A933";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "f[0:19]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 1.41371625 1.8321808799999999 ;
	setAttr ".ro" -type "double3" 0 -89.710629839999996 90 ;
createNode polyCut -n "polyCut2";
	rename -uid "304DCF5E-4F1E-5661-5330-5E9176379088";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "f[60:79]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 2.1954930400000001 1.685429 ;
	setAttr ".ro" -type "double3" 0 -89.681693390000007 90 ;
createNode polyTweak -n "polyTweak1";
	rename -uid "178FCDD2-4F00-4F35-5AD0-579BF29F5FE8";
	setAttr ".uopa" yes;
	setAttr -s 62 ".tk[0:61]" -type "float3"  -0.52659947 -0.86367244 -1.11013997
		 -0.44795305 -0.76520073 -0.90741324 -0.32545671 -0.68705559 -0.74652946 -0.17110288
		 -0.63688314 -0.64323664 -6.6006166e-008 -0.61959428 -0.60764617 0.17110264 -0.6368832
		 -0.64323676 0.32545671 -0.68705553 -0.74653167 0.44795251 -0.76520079 -0.90741342
		 0.52659976 -0.86367249 -1.11014009 0.55369997 -0.97282594 -1.33485866 0.52659976
		 -1.081980824 -1.55957973 0.44795245 -1.18044972 -1.76230621 0.32545662 -1.25859487
		 -1.92319047 0.17110255 -1.30877042 -2.026482105 -4.9504575e-008 -1.32605565 -2.062073231
		 -0.1711027 -1.3087703 -2.026481867 -0.32545671 -1.25859475 -1.92319036 -0.44795251
		 -1.18044972 -1.76230597 -0.52659976 -1.081980944 -1.55957973 -0.55369997 -0.97282594
		 -1.33485866 0 -1.1920929e-007 5.9604645e-008 0 5.9604645e-008 -5.9604645e-008 0 -5.9604645e-008
		 -1.7881393e-007 0 2.9802322e-008 -2.9802322e-007 0 1.4901161e-007 2.3841858e-007
		 0 2.0861626e-007 -3.5762787e-007 0 -2.9802322e-008 -1.7881393e-007 0 1.1920929e-007
		 -1.1920929e-007 0 -1.7881393e-007 0 0 0 -5.9604645e-008 0 0 2.3841858e-007 0 1.1920929e-007
		 0 0 0 -1.1920929e-007 0 -1.1920929e-007 1.1920929e-007 0 3.5762787e-007 -1.1920929e-007
		 0 -2.3841858e-007 1.1920929e-007 0 1.1920929e-007 -1.7881393e-007 0 1.1920929e-007
		 5.9604645e-008 0 0 2.9802322e-007 0 0 -5.9604645e-008 -6.6006166e-008 -1.43819284
		 -2.86334276 0 0 -5.9604645e-008 2.9802322e-008 0.12076789 0.023914156 4.3655746e-010
		 0.22971399 0.045487717 0 0.31617439 0.062608033 5.9604645e-008 0.37168512 0.073600173
		 -5.9604645e-008 0.39081287 0.077388018 1.1920929e-007 0.37168509 0.073600233 0 0.31617415
		 0.062608048 0 0.22971393 0.045487568 5.9604645e-008 0.1207678 0.023914181 -5.9604645e-008
		 -1.7881393e-007 5.2154064e-008 2.9802322e-008 -0.12076777 -0.023914382 1.4173565e-008
		 -0.2297141 -0.045487553 -2.9802322e-008 -0.31617457 -0.062608123 1.1920929e-007 -0.37168503
		 -0.073600352 1.1920929e-007 -0.39081299 -0.077387959 -1.1920929e-007 -0.37168485
		 -0.073600471 0 -0.31617445 -0.062608093 1.1920929e-007 -0.22971404 -0.045487583 0
		 -0.12076789 -0.023914143 0 -1.1920929e-007 -1.1920929e-007;
createNode polyCut -n "polyCut3";
	rename -uid "E01E6C71-4284-A136-A0A7-2B8E64FB3BCE";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "f[60:79]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 4.3244559899999997 1.685429 ;
	setAttr ".ro" -type "double3" 0 -89.769897700000001 90 ;
createNode polyTweak -n "polyTweak2";
	rename -uid "0B6C45F7-4DFB-CA63-F976-CC83FCDD0AED";
	setAttr ".uopa" yes;
	setAttr -s 41 ".tk";
	setAttr ".tk[20]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[21]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[22]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[23]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[24]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[25]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[26]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[27]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[28]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[29]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[30]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[31]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[32]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[33]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[34]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[35]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[36]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[37]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[38]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[39]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[41]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[62]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[63]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[64]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[65]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[66]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[67]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[68]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[69]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[70]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[71]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[72]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[73]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[74]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[75]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[76]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[77]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[78]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[79]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[80]" -type "float3" 0 3.0382094 0 ;
	setAttr ".tk[81]" -type "float3" 0 3.0382094 0 ;
createNode polyCut -n "polyCut4";
	rename -uid "DC016F62-4784-ECB2-94A3-D79C019BEFE8";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "f[60:79]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 3.3930346999999998 1.41930863 ;
	setAttr ".ro" -type "double3" 0 -89.716359839999996 90 ;
createNode polyCut -n "polyCut5";
	rename -uid "A09EF304-4FA2-3736-D88F-8FAB261A4DFA";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "f[60:79]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 2.46161341 1.50801542 ;
	setAttr ".ro" -type "double3" 0 -89.686911420000001 90 ;
createNode polyCut -n "polyCut6";
	rename -uid "0B29093B-4B05-B6C8-D745-6AA787CDF051";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 2 "f[0:19]" "f[60:159]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 2.008417333885343 0 1;
	setAttr ".pc" -type "double3" 100 2.0564547900000001 -2.4137888799999998 ;
	setAttr ".ro" -type "double3" 0 19.069193540000004 90 ;
createNode polyTweak -n "polyTweak3";
	rename -uid "A419C9C8-4200-2D20-5BB7-178ED52805FB";
	setAttr ".uopa" yes;
	setAttr -s 142 ".tk[0:141]" -type "float3"  0 0.46140817 -1.3935045 0
		 0.48703536 -1.32632017 0 0.50737435 -1.27300334 0 0.52043319 -1.2387718 0 0.52493387
		 -1.22697568 0 0.52043331 -1.2387718 0 0.50737542 -1.27300286 0 0.48703536 -1.32632017
		 0 0.46140817 -1.3935045 0 0.4329966 -1.46797764 0 0.40458643 -1.54245186 0 0.3789587
		 -1.60963464 0 0.35862014 -1.66295099 0 0.34556109 -1.69718504 0 0.34106013 -1.70897841
		 0 0.34556103 -1.69718492 0 0.35862008 -1.66295075 0 0.37895852 -1.60963464 0 0.40458643
		 -1.54245198 0 0.4329966 -1.46797764 0 -2.5772419 -0.13057801 0 -2.58101535 -0.13055211
		 0 -2.58401132 -0.13053177 0 -2.58593369 -0.13051906 0 -2.58659577 -0.13051368 0 -2.58593369
		 -0.13051906 0 -2.58401108 -0.13053161 0 -2.58101559 -0.13055232 0 -2.5772419 -0.13057795
		 0 -2.57305717 -0.13060595 0 -2.5688746 -0.13063569 0 -2.56510043 -0.13066119 0 -2.56210542
		 -0.13068056 0 -2.56018257 -0.13069397 0 -2.55951977 -0.13069816 0 -2.56018257 -0.13069391
		 0 -2.56210542 -0.13068056 0 -2.56510043 -0.13066119 0 -2.5688746 -0.13063569 0 -2.57305717
		 -0.13060595 0 1.35642719 -1.47018266 0 -2.57305717 -0.13060595 0 -0.39636329 -0.81995428
		 0 -0.27201876 -0.71749812 0 -0.17333807 -0.63618803 0 -0.10998137 -0.58398384 0 -0.088150285
		 -0.56599551 0 -0.10998143 -0.58398384 0 -0.17333817 -0.63618815 0 -0.27201882 -0.71749812
		 0 -0.39636335 -0.81995428 0 -0.53420049 -0.93352824 0 -0.6720379 -1.047101617 0 -0.79638267
		 -1.14955807 0 -0.89506328 -1.23086774 0 -0.9584198 -1.28307199 0 -0.98025107 -1.30106068
		 0 -0.9584198 -1.28307188 0 -0.89506328 -1.23086774 0 -0.79638267 -1.14955807 0 -0.67203796
		 -1.047101736 0 -0.53420043 -0.93352818 0 -2.17791533 -0.11942476 0 -2.1815002 -0.11938093
		 0 -2.1843214 -0.11934579 0 -2.18612075 -0.11932375 0 -2.1867373 -0.11931591 0 -2.18612051
		 -0.11932385 0 -2.18432164 -0.11934569 0 -2.1815002 -0.11938093 0 -2.17791557 -0.11942483
		 0 -2.17391181 -0.11947479 0 -2.16988206 -0.11952443 0 -2.16622925 -0.11956915 0 -2.1633215
		 -0.11960518 0 -2.16144896 -0.11962839 0 -2.16080356 -0.11963588 0 -2.16144896 -0.11962833
		 0 -2.16332102 -0.11960537 0 -2.16622901 -0.11956927 0 -2.16988206 -0.11952443 0 -2.17391181
		 -0.11947472 0 -1.66071153 -0.14755218 0 -1.65623701 -0.14753218 0 -1.65270805 -0.1475163
		 0 -1.65045464 -0.1475061 0 -1.64968121 -0.14750282 0 -1.65045464 -0.14750595 0 -1.65270793
		 -0.14751615 0 -1.65623701 -0.14753218 0 -1.66071153 -0.14755224 0 -1.66570342 -0.14757471
		 0 -1.67072225 -0.14759742 0 -1.6752702 -0.14761795 0 -1.67889035 -0.14763458 0 -1.68122125
		 -0.14764459 0 -1.68202281 -0.14764903 0 -1.68122125 -0.14764448 0 -1.67889035 -0.14763452
		 0 -1.67526996 -0.1476181 0 -1.67072248 -0.14759742 0 -1.66570342 -0.14757462 0 -1.24401116
		 -0.25659609 0 -1.20468497 -0.25381041 0 -1.1736238 -0.25160989 0 -1.15375829 -0.25020272
		 0 -1.14692783 -0.24971864 0 -1.15375829 -0.25020278 0 -1.1736238 -0.25160995 0 -1.20468497
		 -0.25381041 0 -1.24401116 -0.25659615 0 -1.2878201 -0.25969949 0 -1.33182883 -0.26281726
		 0 -1.37168169 -0.26564074 0 -1.40340304 -0.26788822 0 -1.42380977 -0.26933396 0 -1.4308486
		 -0.26983258 0 -1.42380953 -0.26933393 0 -1.40340304 -0.26788816 0 -1.37168145 -0.26564077
		 0 -1.33182883 -0.26281726 0 -1.2878201 -0.25969952 0 -0.84048539 -0.44373426 0 -0.74565715
		 -0.42628261 0 -0.6706292 -0.41247502 0 -0.62256318 -0.40362933 0 -0.60601944 -0.40058467
		 0 -0.6225633 -0.40362939 0 -0.67062932 -0.41247508 0 -0.74565715 -0.42628267 0 -0.84048551
		 -0.44373432 0 -0.94597799 -0.46314839 0 -1.051854134 -0.48263314 0 -1.14768314 -0.50026894
		 0 -1.22393799 -0.51430243 0 -1.2729888 -0.52332956 0 -1.28990602 -0.52644318 0 -1.27298856
		 -0.52332962 0 -1.22393799 -0.51430249 0 -1.14768314 -0.50026894 0 -1.051854134 -0.48263314
		 0 -0.94597799 -0.46314839;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "5587C21E-4037-142D-FAF3-85B6F9CAA753";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n"
		+ "                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n"
		+ "                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n"
		+ "                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 814\n                -height 330\n                -sceneRenderFilter 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n"
		+ "            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n"
		+ "            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 814\n            -height 330\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n"
		+ "                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n"
		+ "                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n"
		+ "                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 813\n                -height 329\n                -sceneRenderFilter 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n"
		+ "            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n"
		+ "            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n"
		+ "            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 813\n            -height 329\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n"
		+ "                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n"
		+ "                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n                -width 814\n                -height 329\n                -sceneRenderFilter 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n"
		+ "            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 814\n            -height 329\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -holdOuts 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 32768\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n"
		+ "                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -depthOfFieldPreview 1\n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n"
		+ "                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -captureSequenceNumber -1\n"
		+ "                -width 1633\n                -height 706\n                -sceneRenderFilter 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n"
		+ "            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n"
		+ "            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1633\n            -height 706\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -docTag \"isolOutln_fromSeln\" \n                -showShapes 0\n                -showReferenceNodes 1\n                -showReferenceMembers 1\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n"
		+ "                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n"
		+ "                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 0\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showReferenceNodes 1\n            -showReferenceMembers 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n"
		+ "            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n"
		+ "            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n"
		+ "                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n"
		+ "                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n"
		+ "                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n"
		+ "                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n"
		+ "                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n"
		+ "                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n"
		+ "                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n"
		+ "                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n"
		+ "                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n"
		+ "                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n"
		+ "                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n"
		+ "                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"sequenceEditorPanel\" -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n"
		+ "                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n"
		+ "                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n"
		+ "                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n"
		+ "\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n"
		+ "\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"profilerPanel\" -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n"
		+ "                -extendToShapes 1\n                -activeTab -1\n                -editorMode \"default\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n"
		+ "                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -activeTab -1\n                -editorMode \"default\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1633\\n    -height 706\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1633\\n    -height 706\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "FB541EEB-4B27-0B2E-5FF2-FCAE4301E0AD";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode polySphere -n "polySphere1";
	rename -uid "F82A9E14-419D-37D2-4930-EE9D4E8DA49A";
createNode polySphere -n "polySphere2";
	rename -uid "3C5D6D4E-4EF8-2985-B003-0F8648741974";
createNode polyUnite -n "polyUnite1";
	rename -uid "6263AD68-42E2-89DD-29D3-3294B90052FF";
createNode polyCBoolOp -n "polyCBoolOp1";
	rename -uid "550094FF-49F4-F002-40DD-68A471498456";
	setAttr ".mg" -type "Int32Array" 0 ;
createNode polySphere -n "polySphere3";
	rename -uid "530B4CA5-41DA-CB24-6B71-CBAC02447149";
	setAttr ".r" 3;
	setAttr ".sa" 14;
	setAttr ".sh" 14;
createNode polySphere -n "polySphere4";
	rename -uid "9500CAB0-45C3-E3AF-B355-D7BE0E6A5331";
createNode polyCylinder -n "polyCylinder2";
	rename -uid "1AD33BF2-4AB7-F878-23F9-C592A72E2BC9";
	setAttr ".sc" 1;
	setAttr ".cuv" 3;
createNode groupId -n "groupId1";
	rename -uid "89B43AEF-4581-EA53-B048-AF9E5D347DC8";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts1";
	rename -uid "CC144D1A-470A-34D9-4EB7-73983C2C7C04";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "f[0:59]";
createNode groupId -n "groupId2";
	rename -uid "253029B4-45DA-7986-6B93-4C856008CC0A";
	setAttr ".ihi" 0;
createNode groupId -n "groupId3";
	rename -uid "79D542CD-44AD-AF2F-EC0A-A7A00895DB86";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts2";
	rename -uid "91F7A55A-456E-3BE5-94D5-45AB86C64E32";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "f[0:399]";
createNode groupId -n "groupId4";
	rename -uid "AC834046-47D0-F61B-5290-52B5D7950479";
	setAttr ".ihi" 0;
createNode polySphere -n "polySphere5";
	rename -uid "364B6ECB-4C14-9113-B191-089C6995208A";
createNode polyCylinder -n "polyCylinder3";
	rename -uid "7657DD5A-4134-3853-0B20-43863EBD9C32";
	setAttr ".sc" 1;
	setAttr ".cuv" 3;
createNode groupId -n "groupId5";
	rename -uid "E44174D2-405D-35A2-B213-E597E9E9CB8A";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts3";
	rename -uid "B0FE1CC8-48BB-96CD-3975-4BBFC027905B";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "f[0:59]";
createNode groupId -n "groupId6";
	rename -uid "3E2A0950-4B42-E8D0-E265-308A1526CB34";
	setAttr ".ihi" 0;
createNode groupId -n "groupId7";
	rename -uid "4A71BC11-40A6-ED5E-314C-CDBF77613529";
	setAttr ".ihi" 0;
createNode groupParts -n "groupParts4";
	rename -uid "AE1C01FA-4611-D3CC-1883-77A99A20F316";
	setAttr ".ihi" 0;
	setAttr ".ic" -type "componentList" 1 "f[0:399]";
createNode groupId -n "groupId8";
	rename -uid "7CD2051C-48CF-D268-DA05-5DADF8FA0184";
	setAttr ".ihi" 0;
createNode polySphere -n "polySphere6";
	rename -uid "42550767-4C07-90E8-D0BF-C081491DC3D9";
createNode polySphere -n "polySphere7";
	rename -uid "C9ABC0AF-4134-C53E-98FB-CAB72E6B46CB";
createNode polyTweakUV -n "polyTweakUV1";
	rename -uid "27132537-49D6-A722-5002-AD9781D09AC8";
	setAttr ".uopa" yes;
	setAttr -s 439 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" 0.014503792 0.67530072 -0.0217974 0.67530072
		 -0.058098629 0.67530072 -0.09439984 0.67530072 -0.13070104 0.67530072 -0.16700223
		 0.67530072 -0.2033035 0.67530072 -0.23960471 0.67530072 -0.27590594 0.67530072 -0.31220716
		 0.67530072 -0.34850836 0.67530072 -0.38480961 0.67530072 -0.42111078 0.67530072 -0.45741206
		 0.67530072 -0.4937132 0.67530072 -0.53001451 0.67530072 -0.56631565 0.67530072 -0.60261691
		 0.67530072 -0.63891816 0.67530072 -0.6752193 0.67530072 -0.71152055 0.67530072 0.014503792
		 0.63899946 -0.0217974 0.63899946 -0.058098629 0.63899946 -0.09439984 0.63899946 -0.13070104
		 0.63899946 -0.16700223 0.63899946 -0.2033035 0.63899946 -0.23960471 0.63899946 -0.27590594
		 0.63899946 -0.31220716 0.63899946 -0.34850836 0.63899946 -0.38480961 0.63899946 -0.42111078
		 0.63899946 -0.45741206 0.63899946 -0.4937132 0.63899946 -0.53001451 0.63899946 -0.56631565
		 0.63899946 -0.60261691 0.63899946 -0.63891816 0.63899946 -0.6752193 0.63899946 -0.71152055
		 0.63899946 0.014503792 0.60269821 -0.0217974 0.60269821 -0.058098629 0.60269821 -0.09439984
		 0.60269821 -0.13070104 0.60269821 -0.16700223 0.60269821 -0.2033035 0.60269821 -0.23960471
		 0.60269821 -0.27590594 0.60269821 -0.31220716 0.60269821 -0.34850836 0.60269821 -0.38480961
		 0.60269821 -0.42111078 0.60269821 -0.45741206 0.60269821 -0.4937132 0.60269821 -0.53001451
		 0.60269821 -0.56631565 0.60269821 -0.60261691 0.60269821 -0.63891816 0.60269821 -0.6752193
		 0.60269821 -0.71152055 0.60269821 0.014503792 0.56639701 -0.0217974 0.56639701 -0.058098629
		 0.56639701 -0.09439984 0.56639701 -0.13070104 0.56639701 -0.16700223 0.56639701 -0.2033035
		 0.56639701 -0.23960471 0.56639701 -0.27590594 0.56639701 -0.31220716 0.56639701 -0.34850836
		 0.56639701 -0.38480961 0.56639701 -0.42111078 0.56639701 -0.45741206 0.56639701 -0.4937132
		 0.56639701 -0.53001451 0.56639701 -0.56631565 0.56639701 -0.60261691 0.56639701 -0.63891816
		 0.56639701 -0.6752193 0.56639701 -0.71152055 0.56639701 0.014503792 0.53009588 -0.0217974
		 0.53009588 -0.058098629 0.53009588 -0.09439984 0.53009588 -0.13070104 0.53009588
		 -0.16700223 0.53009588 -0.2033035 0.53009588 -0.23960471 0.53009588 -0.27590594 0.53009588
		 -0.31220716 0.53009588 -0.34850836 0.53009588 -0.38480961 0.53009588 -0.42111078
		 0.53009588 -0.45741206 0.53009588 -0.4937132 0.53009588 -0.53001451 0.53009588 -0.56631565
		 0.53009588 -0.60261691 0.53009588 -0.63891816 0.53009588 -0.6752193 0.53009588 -0.71152055
		 0.53009588 0.014503792 0.49379462 -0.0217974 0.49379462 -0.058098629 0.49379462 -0.09439984
		 0.49379462 -0.13070104 0.49379462 -0.16700223 0.49379462 -0.2033035 0.49379462 -0.23960471
		 0.49379462 -0.27590594 0.49379462 -0.31220716 0.49379462 -0.34850836 0.49379462 -0.38480961
		 0.49379462 -0.42111078 0.49379462 -0.45741206 0.49379462 -0.4937132 0.49379462 -0.53001451
		 0.49379462 -0.56631565 0.49379462 -0.60261691 0.49379462 -0.63891816 0.49379462 -0.6752193
		 0.49379462 -0.71152055 0.49379462 0.014503792 0.45749342 -0.0217974 0.45749342 -0.058098629
		 0.45749342 -0.09439984 0.45749342 -0.13070104 0.45749342 -0.16700223 0.45749342 -0.2033035
		 0.45749342 -0.23960471 0.45749342 -0.27590594 0.45749342 -0.31220716 0.45749342 -0.34850836
		 0.45749342 -0.38480961 0.45749342 -0.42111078 0.45749342 -0.45741206 0.45749342 -0.4937132
		 0.45749342 -0.53001451 0.45749342 -0.56631565 0.45749342 -0.60261691 0.45749342 -0.63891816
		 0.45749342 -0.6752193 0.45749342 -0.71152055 0.45749342 0.014503792 0.42119223 -0.0217974
		 0.42119223 -0.058098629 0.42119223 -0.09439984 0.42119223 -0.13070104 0.42119223
		 -0.16700223 0.42119223 -0.2033035 0.42119223 -0.23960471 0.42119223 -0.27590594 0.42119223
		 -0.31220716 0.42119223 -0.34850836 0.42119223 -0.38480961 0.42119223 -0.42111078
		 0.42119223 -0.45741206 0.42119223 -0.4937132 0.42119223 -0.53001451 0.42119223 -0.56631565
		 0.42119223 -0.60261691 0.42119223 -0.63891816 0.42119223 -0.6752193 0.42119223 -0.71152055
		 0.42119223 0.014503792 0.38489097 -0.0217974 0.38489097 -0.058098629 0.38489097 -0.09439984
		 0.38489097 -0.13070104 0.38489097 -0.16700223 0.38489097 -0.2033035 0.38489097 -0.23960471
		 0.38489097 -0.27590594 0.38489097 -0.31220716 0.38489097 -0.34850836 0.38489097 -0.38480961
		 0.38489097 -0.42111078 0.38489097 -0.45741206 0.38489097 -0.4937132 0.38489097 -0.53001451
		 0.38489097 -0.56631565 0.38489097 -0.60261691 0.38489097 -0.63891816 0.38489097 -0.6752193
		 0.38489097 -0.71152055 0.38489097 0.014503792 0.34858981 -0.0217974 0.34858981 -0.058098629
		 0.34858981 -0.09439984 0.34858981 -0.13070104 0.34858981 -0.16700223 0.34858981 -0.2033035
		 0.34858981 -0.23960471 0.34858981 -0.27590594 0.34858981 -0.31220716 0.34858981 -0.34850836
		 0.34858981 -0.38480961 0.34858981 -0.42111078 0.34858981 -0.45741206 0.34858981 -0.4937132
		 0.34858981 -0.53001451 0.34858981 -0.56631565 0.34858981 -0.60261691 0.34858981 -0.63891816
		 0.34858981 -0.6752193 0.34858981 -0.71152055 0.34858981 0.014503792 0.31228852 -0.0217974
		 0.31228852 -0.058098629 0.31228852 -0.09439984 0.31228852 -0.13070104 0.31228852
		 -0.16700223 0.31228852 -0.2033035 0.31228852 -0.23960471 0.31228852 -0.27590594 0.31228852
		 -0.31220716 0.31228852 -0.34850836 0.31228852 -0.38480961 0.31228852 -0.42111078
		 0.31228852 -0.45741206 0.31228852 -0.4937132 0.31228852 -0.53001451 0.31228852 -0.56631565
		 0.31228852 -0.60261691 0.31228852 -0.63891816 0.31228852 -0.6752193 0.31228852 -0.71152055
		 0.31228852 0.014503792 0.27598727 -0.0217974 0.27598727 -0.058098629 0.27598727 -0.09439984
		 0.27598727 -0.13070104 0.27598727 -0.16700223 0.27598727 -0.2033035 0.27598727 -0.23960471
		 0.27598727 -0.27590594 0.27598727 -0.31220716 0.27598727 -0.34850836 0.27598727 -0.38480961
		 0.27598727 -0.42111078 0.27598727 -0.45741206 0.27598727 -0.4937132 0.27598727 -0.53001451
		 0.27598727 -0.56631565 0.27598727 -0.60261691 0.27598727 -0.63891816 0.27598727;
	setAttr ".uvtk[250:438]" -0.6752193 0.27598727 -0.71152055 0.27598727 0.014503792
		 0.23968604 -0.0217974 0.23968604 -0.058098629 0.23968604 -0.09439984 0.23968604 -0.13070104
		 0.23968604 -0.16700223 0.23968604 -0.2033035 0.23968604 -0.23960471 0.23968604 -0.27590594
		 0.23968604 -0.31220716 0.23968604 -0.34850836 0.23968604 -0.38480961 0.23968604 -0.42111078
		 0.23968604 -0.45741206 0.23968604 -0.4937132 0.23968604 -0.53001451 0.23968604 -0.56631565
		 0.23968604 -0.60261691 0.23968604 -0.63891816 0.23968604 -0.6752193 0.23968604 -0.71152055
		 0.23968604 0.014503792 0.20338494 -0.0217974 0.20338494 -0.058098629 0.20338494 -0.09439984
		 0.20338494 -0.13070104 0.20338494 -0.16700223 0.20338494 -0.2033035 0.20338494 -0.23960471
		 0.20338494 -0.27590594 0.20338494 -0.31220716 0.20338494 -0.34850836 0.20338494 -0.38480961
		 0.20338494 -0.42111078 0.20338494 -0.45741206 0.20338494 -0.4937132 0.20338494 -0.53001451
		 0.20338494 -0.56631565 0.20338494 -0.60261691 0.20338494 -0.63891816 0.20338494 -0.6752193
		 0.20338494 -0.71152055 0.20338494 0.014503792 0.16708368 -0.0217974 0.16708368 -0.058098629
		 0.16708368 -0.09439984 0.16708368 -0.13070104 0.16708368 -0.16700223 0.16708368 -0.2033035
		 0.16708368 -0.23960471 0.16708368 -0.27590594 0.16708368 -0.31220716 0.16708368 -0.34850836
		 0.16708368 -0.38480961 0.16708368 -0.42111078 0.16708368 -0.45741206 0.16708368 -0.4937132
		 0.16708368 -0.53001451 0.16708368 -0.56631565 0.16708368 -0.60261691 0.16708368 -0.63891816
		 0.16708368 -0.6752193 0.16708368 -0.71152055 0.16708368 0.014503792 0.13078228 -0.0217974
		 0.13078228 -0.058098629 0.13078228 -0.09439984 0.13078228 -0.13070104 0.13078228
		 -0.16700223 0.13078228 -0.2033035 0.13078228 -0.23960471 0.13078228 -0.27590594 0.13078228
		 -0.31220716 0.13078228 -0.34850836 0.13078228 -0.38480961 0.13078228 -0.42111078
		 0.13078228 -0.45741206 0.13078228 -0.4937132 0.13078228 -0.53001451 0.13078228 -0.56631565
		 0.13078228 -0.60261691 0.13078228 -0.63891816 0.13078228 -0.6752193 0.13078228 -0.71152055
		 0.13078228 0.014503792 0.094481193 -0.0217974 0.094481193 -0.058098629 0.094481193
		 -0.09439984 0.094481193 -0.13070104 0.094481193 -0.16700223 0.094481193 -0.2033035
		 0.094481193 -0.23960471 0.094481193 -0.27590594 0.094481193 -0.31220716 0.094481193
		 -0.34850836 0.094481193 -0.38480961 0.094481193 -0.42111078 0.094481193 -0.45741206
		 0.094481193 -0.4937132 0.094481193 -0.53001451 0.094481193 -0.56631565 0.094481193
		 -0.60261691 0.094481193 -0.63891816 0.094481193 -0.6752193 0.094481193 -0.71152055
		 0.094481193 0.014503792 0.058180071 -0.0217974 0.058180071 -0.058098629 0.058180071
		 -0.09439984 0.058180071 -0.13070104 0.058180071 -0.16700223 0.058180071 -0.2033035
		 0.058180071 -0.23960471 0.058180071 -0.27590594 0.058180071 -0.31220716 0.058180071
		 -0.34850836 0.058180071 -0.38480961 0.058180071 -0.42111078 0.058180071 -0.45741206
		 0.058180071 -0.4937132 0.058180071 -0.53001451 0.058180071 -0.56631565 0.058180071
		 -0.60261691 0.058180071 -0.63891816 0.058180071 -0.6752193 0.058180071 -0.71152055
		 0.058180071 0.014503792 0.021878785 -0.0217974 0.021878785 -0.058098629 0.021878785
		 -0.09439984 0.021878785 -0.13070104 0.021878785 -0.16700223 0.021878785 -0.2033035
		 0.021878785 -0.23960471 0.021878785 -0.27590594 0.021878785 -0.31220716 0.021878785
		 -0.34850836 0.021878785 -0.38480961 0.021878785 -0.42111078 0.021878785 -0.45741206
		 0.021878785 -0.4937132 0.021878785 -0.53001451 0.021878785 -0.56631565 0.021878785
		 -0.60261691 0.021878785 -0.63891816 0.021878785 -0.6752193 0.021878785 -0.71152055
		 0.021878785 -0.0036468157 0.71160197 -0.039948002 0.71160197 -0.076249219 0.71160197
		 -0.11255039 0.71160197 -0.14885163 0.71160197 -0.18515287 0.71160197 -0.22145408
		 0.71160197 -0.25775528 0.71160197 -0.2940565 0.71160197 -0.3303577 0.71160197 -0.36665899
		 0.71160197 -0.40296012 0.71160197 -0.43926132 0.71160197 -0.47556257 0.71160197 -0.51186377
		 0.71160197 -0.54816496 0.71160197 -0.58446616 0.71160197 -0.62076735 0.71160197 -0.65706861
		 0.71160197 -0.69336981 0.71160197 -0.0036468157 -0.014422288 -0.039948002 -0.014422288
		 -0.076249219 -0.014422288 -0.11255039 -0.014422288 -0.14885163 -0.014422288 -0.18515287
		 -0.014422288 -0.22145408 -0.014422288 -0.25775528 -0.014422288 -0.2940565 -0.014422288
		 -0.3303577 -0.014422288 -0.36665899 -0.014422288 -0.40296012 -0.014422288 -0.43926132
		 -0.014422288 -0.47556257 -0.014422288 -0.51186377 -0.014422288 -0.54816496 -0.014422288
		 -0.58446616 -0.014422288 -0.62076735 -0.014422288 -0.65706861 -0.014422288 -0.69336981
		 -0.014422288;
createNode polyTweakUV -n "polyTweakUV2";
	rename -uid "6F365B44-41CE-5DDC-4AC6-93B52455BF7A";
	setAttr ".uopa" yes;
	setAttr -s 439 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" 0.012344226 0.67531818 -0.02384853
		 0.67531818 -0.060041286 0.67531818 -0.096234046 0.67531818 -0.1324268 0.67531818
		 -0.16861954 0.67531818 -0.20481232 0.67531818 -0.24100509 0.67531818 -0.27719784
		 0.67531818 -0.31339064 0.67531818 -0.34958339 0.67531818 -0.38577619 0.67531818 -0.42196894
		 0.67531818 -0.45816171 0.67531818 -0.49435449 0.67531818 -0.53054726 0.67531818 -0.56674004
		 0.67531818 -0.60293281 0.67531818 -0.63912559 0.67531818 -0.67531836 0.67531818 -0.71151102
		 0.67531818 0.012344226 0.63912547 -0.02384853 0.63912547 -0.060041286 0.63912547
		 -0.096234046 0.63912547 -0.1324268 0.63912547 -0.16861954 0.63912547 -0.20481232
		 0.63912547 -0.24100509 0.63912547 -0.27719784 0.63912547 -0.31339064 0.63912547 -0.34958339
		 0.63912547 -0.38577619 0.63912547 -0.42196894 0.63912547 -0.45816171 0.63912547 -0.49435449
		 0.63912547 -0.53054726 0.63912547 -0.56674004 0.63912547 -0.60293281 0.63912547 -0.63912559
		 0.63912547 -0.67531836 0.63912547 -0.71151102 0.63912547 0.012344226 0.60293263 -0.02384853
		 0.60293263 -0.060041286 0.60293263 -0.096234046 0.60293263 -0.1324268 0.60293263
		 -0.16861954 0.60293263 -0.20481232 0.60293263 -0.24100509 0.60293263 -0.27719784
		 0.60293263 -0.31339064 0.60293263 -0.34958339 0.60293263 -0.38577619 0.60293263 -0.42196894
		 0.60293263 -0.45816171 0.60293263 -0.49435449 0.60293263 -0.53054726 0.60293263 -0.56674004
		 0.60293263 -0.60293281 0.60293263 -0.63912559 0.60293263 -0.67531836 0.60293263 -0.71151102
		 0.60293263 0.012344226 0.56673998 -0.02384853 0.56673998 -0.060041286 0.56673998
		 -0.096234046 0.56673998 -0.1324268 0.56673998 -0.16861954 0.56673998 -0.20481232
		 0.56673998 -0.24100509 0.56673998 -0.27719784 0.56673998 -0.31339064 0.56673998 -0.34958339
		 0.56673998 -0.38577619 0.56673998 -0.42196894 0.56673998 -0.45816171 0.56673998 -0.49435449
		 0.56673998 -0.53054726 0.56673998 -0.56674004 0.56673998 -0.60293281 0.56673998 -0.63912559
		 0.56673998 -0.67531836 0.56673998 -0.71151102 0.56673998 0.012344226 0.53054714 -0.02384853
		 0.53054714 -0.060041286 0.53054714 -0.096234046 0.53054714 -0.1324268 0.53054714
		 -0.16861954 0.53054714 -0.20481232 0.53054714 -0.24100509 0.53054714 -0.27719784
		 0.53054714 -0.31339064 0.53054714 -0.34958339 0.53054714 -0.38577619 0.53054714 -0.42196894
		 0.53054714 -0.45816171 0.53054714 -0.49435449 0.53054714 -0.53054726 0.53054714 -0.56674004
		 0.53054714 -0.60293281 0.53054714 -0.63912559 0.53054714 -0.67531836 0.53054714 -0.71151102
		 0.53054714 0.012344226 0.4943544 -0.02384853 0.4943544 -0.060041286 0.4943544 -0.096234046
		 0.4943544 -0.1324268 0.4943544 -0.16861954 0.4943544 -0.20481232 0.4943544 -0.24100509
		 0.4943544 -0.27719784 0.4943544 -0.31339064 0.4943544 -0.34958339 0.4943544 -0.38577619
		 0.4943544 -0.42196894 0.4943544 -0.45816171 0.4943544 -0.49435449 0.4943544 -0.53054726
		 0.4943544 -0.56674004 0.4943544 -0.60293281 0.4943544 -0.63912559 0.4943544 -0.67531836
		 0.4943544 -0.71151102 0.4943544 0.012344226 0.45816162 -0.02384853 0.45816162 -0.060041286
		 0.45816162 -0.096234046 0.45816162 -0.1324268 0.45816162 -0.16861954 0.45816162 -0.20481232
		 0.45816162 -0.24100509 0.45816162 -0.27719784 0.45816162 -0.31339064 0.45816162 -0.34958339
		 0.45816162 -0.38577619 0.45816162 -0.42196894 0.45816162 -0.45816171 0.45816162 -0.49435449
		 0.45816162 -0.53054726 0.45816162 -0.56674004 0.45816162 -0.60293281 0.45816162 -0.63912559
		 0.45816162 -0.67531836 0.45816162 -0.71151102 0.45816162 0.012344226 0.42196891 -0.02384853
		 0.42196891 -0.060041286 0.42196891 -0.096234046 0.42196891 -0.1324268 0.42196891
		 -0.16861954 0.42196891 -0.20481232 0.42196891 -0.24100509 0.42196891 -0.27719784
		 0.42196891 -0.31339064 0.42196891 -0.34958339 0.42196891 -0.38577619 0.42196891 -0.42196894
		 0.42196891 -0.45816171 0.42196891 -0.49435449 0.42196891 -0.53054726 0.42196891 -0.56674004
		 0.42196891 -0.60293281 0.42196891 -0.63912559 0.42196891 -0.67531836 0.42196891 -0.71151102
		 0.42196891 0.012344226 0.38577619 -0.02384853 0.38577619 -0.060041286 0.38577619
		 -0.096234046 0.38577619 -0.1324268 0.38577619 -0.16861954 0.38577619 -0.20481232
		 0.38577619 -0.24100509 0.38577619 -0.27719784 0.38577619 -0.31339064 0.38577619 -0.34958339
		 0.38577619 -0.38577619 0.38577619 -0.42196894 0.38577619 -0.45816171 0.38577619 -0.49435449
		 0.38577619 -0.53054726 0.38577619 -0.56674004 0.38577619 -0.60293281 0.38577619 -0.63912559
		 0.38577619 -0.67531836 0.38577619 -0.71151102 0.38577619 0.012344226 0.34958336 -0.02384853
		 0.34958336 -0.060041286 0.34958336 -0.096234046 0.34958336 -0.1324268 0.34958336
		 -0.16861954 0.34958336 -0.20481232 0.34958336 -0.24100509 0.34958336 -0.27719784
		 0.34958336 -0.31339064 0.34958336 -0.34958339 0.34958336 -0.38577619 0.34958336 -0.42196894
		 0.34958336 -0.45816171 0.34958336 -0.49435449 0.34958336 -0.53054726 0.34958336 -0.56674004
		 0.34958336 -0.60293281 0.34958336 -0.63912559 0.34958336 -0.67531836 0.34958336 -0.71151102
		 0.34958336 0.012344226 0.31339061 -0.02384853 0.31339061 -0.060041286 0.31339061
		 -0.096234046 0.31339061 -0.1324268 0.31339061 -0.16861954 0.31339061 -0.20481232
		 0.31339061 -0.24100509 0.31339061 -0.27719784 0.31339061 -0.31339064 0.31339061 -0.34958339
		 0.31339061 -0.38577619 0.31339061 -0.42196894 0.31339061 -0.45816171 0.31339061 -0.49435449
		 0.31339061 -0.53054726 0.31339061 -0.56674004 0.31339061 -0.60293281 0.31339061 -0.63912559
		 0.31339061 -0.67531836 0.31339061 -0.71151102 0.31339061 0.012344226 0.27719778 -0.02384853
		 0.27719778 -0.060041286 0.27719778 -0.096234046 0.27719778 -0.1324268 0.27719778
		 -0.16861954 0.27719778 -0.20481232 0.27719778 -0.24100509 0.27719778 -0.27719784
		 0.27719778 -0.31339064 0.27719778 -0.34958339 0.27719778 -0.38577619 0.27719778 -0.42196894
		 0.27719778 -0.45816171 0.27719778 -0.49435449 0.27719778 -0.53054726 0.27719778 -0.56674004
		 0.27719778 -0.60293281 0.27719778 -0.63912559 0.27719778;
	setAttr ".uvtk[250:438]" -0.67531836 0.27719778 -0.71151102 0.27719778 0.012344226
		 0.24100506 -0.02384853 0.24100506 -0.060041286 0.24100506 -0.096234046 0.24100506
		 -0.1324268 0.24100506 -0.16861954 0.24100506 -0.20481232 0.24100506 -0.24100509 0.24100506
		 -0.27719784 0.24100506 -0.31339064 0.24100506 -0.34958339 0.24100506 -0.38577619
		 0.24100506 -0.42196894 0.24100506 -0.45816171 0.24100506 -0.49435449 0.24100506 -0.53054726
		 0.24100506 -0.56674004 0.24100506 -0.60293281 0.24100506 -0.63912559 0.24100506 -0.67531836
		 0.24100506 -0.71151102 0.24100506 0.012344226 0.20481223 -0.02384853 0.20481223 -0.060041286
		 0.20481223 -0.096234046 0.20481223 -0.1324268 0.20481223 -0.16861954 0.20481223 -0.20481232
		 0.20481223 -0.24100509 0.20481223 -0.27719784 0.20481223 -0.31339064 0.20481223 -0.34958339
		 0.20481223 -0.38577619 0.20481223 -0.42196894 0.20481223 -0.45816171 0.20481223 -0.49435449
		 0.20481223 -0.53054726 0.20481223 -0.56674004 0.20481223 -0.60293281 0.20481223 -0.63912559
		 0.20481223 -0.67531836 0.20481223 -0.71151102 0.20481223 0.012344226 0.16861951 -0.02384853
		 0.16861951 -0.060041286 0.16861951 -0.096234046 0.16861951 -0.1324268 0.16861951
		 -0.16861954 0.16861951 -0.20481232 0.16861951 -0.24100509 0.16861951 -0.27719784
		 0.16861951 -0.31339064 0.16861951 -0.34958339 0.16861951 -0.38577619 0.16861951 -0.42196894
		 0.16861951 -0.45816171 0.16861951 -0.49435449 0.16861951 -0.53054726 0.16861951 -0.56674004
		 0.16861951 -0.60293281 0.16861951 -0.63912559 0.16861951 -0.67531836 0.16861951 -0.71151102
		 0.16861951 0.012344226 0.13242674 -0.02384853 0.13242674 -0.060041286 0.13242674
		 -0.096234046 0.13242674 -0.1324268 0.13242674 -0.16861954 0.13242674 -0.20481232
		 0.13242674 -0.24100509 0.13242674 -0.27719784 0.13242674 -0.31339064 0.13242674 -0.34958339
		 0.13242674 -0.38577619 0.13242674 -0.42196894 0.13242674 -0.45816171 0.13242674 -0.49435449
		 0.13242674 -0.53054726 0.13242674 -0.56674004 0.13242674 -0.60293281 0.13242674 -0.63912559
		 0.13242674 -0.67531836 0.13242674 -0.71151102 0.13242674 0.012344226 0.096234024
		 -0.02384853 0.096234024 -0.060041286 0.096234024 -0.096234046 0.096234024 -0.1324268
		 0.096234024 -0.16861954 0.096234024 -0.20481232 0.096234024 -0.24100509 0.096234024
		 -0.27719784 0.096234024 -0.31339064 0.096234024 -0.34958339 0.096234024 -0.38577619
		 0.096234024 -0.42196894 0.096234024 -0.45816171 0.096234024 -0.49435449 0.096234024
		 -0.53054726 0.096234024 -0.56674004 0.096234024 -0.60293281 0.096234024 -0.63912559
		 0.096234024 -0.67531836 0.096234024 -0.71151102 0.096234024 0.012344226 0.060041249
		 -0.02384853 0.060041249 -0.060041286 0.060041249 -0.096234046 0.060041249 -0.1324268
		 0.060041249 -0.16861954 0.060041249 -0.20481232 0.060041249 -0.24100509 0.060041249
		 -0.27719784 0.060041249 -0.31339064 0.060041249 -0.34958339 0.060041249 -0.38577619
		 0.060041249 -0.42196894 0.060041249 -0.45816171 0.060041249 -0.49435449 0.060041249
		 -0.53054726 0.060041249 -0.56674004 0.060041249 -0.60293281 0.060041249 -0.63912559
		 0.060041249 -0.67531836 0.060041249 -0.71151102 0.060041249 0.012344226 0.023848474
		 -0.02384853 0.023848474 -0.060041286 0.023848474 -0.096234046 0.023848474 -0.1324268
		 0.023848474 -0.16861954 0.023848474 -0.20481232 0.023848474 -0.24100509 0.023848474
		 -0.27719784 0.023848474 -0.31339064 0.023848474 -0.34958339 0.023848474 -0.38577619
		 0.023848474 -0.42196894 0.023848474 -0.45816171 0.023848474 -0.49435449 0.023848474
		 -0.53054726 0.023848474 -0.56674004 0.023848474 -0.60293281 0.023848474 -0.63912559
		 0.023848474 -0.67531836 0.023848474 -0.71151102 0.023848474 -0.0057521546 0.7115109
		 -0.041944936 0.7115109 -0.078137666 0.7115109 -0.11433044 0.7115109 -0.15052322 0.7115109
		 -0.18671595 0.7115109 -0.22290872 0.7115109 -0.25910148 0.7115109 -0.29529423 0.7115109
		 -0.331487 0.7115109 -0.36767977 0.7115109 -0.40387249 0.7115109 -0.44006526 0.7115109
		 -0.47625801 0.7115109 -0.51245081 0.7115109 -0.54864359 0.7115109 -0.5848363 0.7115109
		 -0.62102914 0.7115109 -0.65722185 0.7115109 -0.69341463 0.7115109 -0.0057521546 -0.012344092
		 -0.041944936 -0.012344092 -0.078137666 -0.012344092 -0.11433044 -0.012344092 -0.15052322
		 -0.012344092 -0.18671595 -0.012344092 -0.22290872 -0.012344092 -0.25910148 -0.012344092
		 -0.29529423 -0.012344092 -0.331487 -0.012344092 -0.36767977 -0.012344092 -0.40387249
		 -0.012344092 -0.44006526 -0.012344092 -0.47625801 -0.012344092 -0.51245081 -0.012344092
		 -0.54864359 -0.012344092 -0.5848363 -0.012344092 -0.62102914 -0.012344092 -0.65722185
		 -0.012344092 -0.69341463 -0.012344092;
createNode polyTweakUV -n "polyTweakUV3";
	rename -uid "5415465E-4392-C373-1AF9-91A70878D30E";
	setAttr ".uopa" yes;
	setAttr -s 439 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" 0.012344226 0.67531818 -0.02384853
		 0.67531818 -0.060041286 0.67531818 -0.096234046 0.67531818 -0.1324268 0.67531818
		 -0.16861954 0.67531818 -0.20481232 0.67531818 -0.24100509 0.67531818 -0.27719784
		 0.67531818 -0.31339064 0.67531818 -0.34958339 0.67531818 -0.38577619 0.67531818 -0.42196894
		 0.67531818 -0.45816171 0.67531818 -0.49435449 0.67531818 -0.53054726 0.67531818 -0.56674004
		 0.67531818 -0.60293281 0.67531818 -0.63912559 0.67531818 -0.67531836 0.67531818 -0.71151102
		 0.67531818 0.012344226 0.63912547 -0.02384853 0.63912547 -0.060041286 0.63912547
		 -0.096234046 0.63912547 -0.1324268 0.63912547 -0.16861954 0.63912547 -0.20481232
		 0.63912547 -0.24100509 0.63912547 -0.27719784 0.63912547 -0.31339064 0.63912547 -0.34958339
		 0.63912547 -0.38577619 0.63912547 -0.42196894 0.63912547 -0.45816171 0.63912547 -0.49435449
		 0.63912547 -0.53054726 0.63912547 -0.56674004 0.63912547 -0.60293281 0.63912547 -0.63912559
		 0.63912547 -0.67531836 0.63912547 -0.71151102 0.63912547 0.012344226 0.60293263 -0.02384853
		 0.60293263 -0.060041286 0.60293263 -0.096234046 0.60293263 -0.1324268 0.60293263
		 -0.16861954 0.60293263 -0.20481232 0.60293263 -0.24100509 0.60293263 -0.27719784
		 0.60293263 -0.31339064 0.60293263 -0.34958339 0.60293263 -0.38577619 0.60293263 -0.42196894
		 0.60293263 -0.45816171 0.60293263 -0.49435449 0.60293263 -0.53054726 0.60293263 -0.56674004
		 0.60293263 -0.60293281 0.60293263 -0.63912559 0.60293263 -0.67531836 0.60293263 -0.71151102
		 0.60293263 0.012344226 0.56673998 -0.02384853 0.56673998 -0.060041286 0.56673998
		 -0.096234046 0.56673998 -0.1324268 0.56673998 -0.16861954 0.56673998 -0.20481232
		 0.56673998 -0.24100509 0.56673998 -0.27719784 0.56673998 -0.31339064 0.56673998 -0.34958339
		 0.56673998 -0.38577619 0.56673998 -0.42196894 0.56673998 -0.45816171 0.56673998 -0.49435449
		 0.56673998 -0.53054726 0.56673998 -0.56674004 0.56673998 -0.60293281 0.56673998 -0.63912559
		 0.56673998 -0.67531836 0.56673998 -0.71151102 0.56673998 0.012344226 0.53054714 -0.02384853
		 0.53054714 -0.060041286 0.53054714 -0.096234046 0.53054714 -0.1324268 0.53054714
		 -0.16861954 0.53054714 -0.20481232 0.53054714 -0.24100509 0.53054714 -0.27719784
		 0.53054714 -0.31339064 0.53054714 -0.34958339 0.53054714 -0.38577619 0.53054714 -0.42196894
		 0.53054714 -0.45816171 0.53054714 -0.49435449 0.53054714 -0.53054726 0.53054714 -0.56674004
		 0.53054714 -0.60293281 0.53054714 -0.63912559 0.53054714 -0.67531836 0.53054714 -0.71151102
		 0.53054714 0.012344226 0.4943544 -0.02384853 0.4943544 -0.060041286 0.4943544 -0.096234046
		 0.4943544 -0.1324268 0.4943544 -0.16861954 0.4943544 -0.20481232 0.4943544 -0.24100509
		 0.4943544 -0.27719784 0.4943544 -0.31339064 0.4943544 -0.34958339 0.4943544 -0.38577619
		 0.4943544 -0.42196894 0.4943544 -0.45816171 0.4943544 -0.49435449 0.4943544 -0.53054726
		 0.4943544 -0.56674004 0.4943544 -0.60293281 0.4943544 -0.63912559 0.4943544 -0.67531836
		 0.4943544 -0.71151102 0.4943544 0.012344226 0.45816162 -0.02384853 0.45816162 -0.060041286
		 0.45816162 -0.096234046 0.45816162 -0.1324268 0.45816162 -0.16861954 0.45816162 -0.20481232
		 0.45816162 -0.24100509 0.45816162 -0.27719784 0.45816162 -0.31339064 0.45816162 -0.34958339
		 0.45816162 -0.38577619 0.45816162 -0.42196894 0.45816162 -0.45816171 0.45816162 -0.49435449
		 0.45816162 -0.53054726 0.45816162 -0.56674004 0.45816162 -0.60293281 0.45816162 -0.63912559
		 0.45816162 -0.67531836 0.45816162 -0.71151102 0.45816162 0.012344226 0.42196891 -0.02384853
		 0.42196891 -0.060041286 0.42196891 -0.096234046 0.42196891 -0.1324268 0.42196891
		 -0.16861954 0.42196891 -0.20481232 0.42196891 -0.24100509 0.42196891 -0.27719784
		 0.42196891 -0.31339064 0.42196891 -0.34958339 0.42196891 -0.38577619 0.42196891 -0.42196894
		 0.42196891 -0.45816171 0.42196891 -0.49435449 0.42196891 -0.53054726 0.42196891 -0.56674004
		 0.42196891 -0.60293281 0.42196891 -0.63912559 0.42196891 -0.67531836 0.42196891 -0.71151102
		 0.42196891 0.012344226 0.38577619 -0.02384853 0.38577619 -0.060041286 0.38577619
		 -0.096234046 0.38577619 -0.1324268 0.38577619 -0.16861954 0.38577619 -0.20481232
		 0.38577619 -0.24100509 0.38577619 -0.27719784 0.38577619 -0.31339064 0.38577619 -0.34958339
		 0.38577619 -0.38577619 0.38577619 -0.42196894 0.38577619 -0.45816171 0.38577619 -0.49435449
		 0.38577619 -0.53054726 0.38577619 -0.56674004 0.38577619 -0.60293281 0.38577619 -0.63912559
		 0.38577619 -0.67531836 0.38577619 -0.71151102 0.38577619 0.012344226 0.34958336 -0.02384853
		 0.34958336 -0.060041286 0.34958336 -0.096234046 0.34958336 -0.1324268 0.34958336
		 -0.16861954 0.34958336 -0.20481232 0.34958336 -0.24100509 0.34958336 -0.27719784
		 0.34958336 -0.31339064 0.34958336 -0.34958339 0.34958336 -0.38577619 0.34958336 -0.42196894
		 0.34958336 -0.45816171 0.34958336 -0.49435449 0.34958336 -0.53054726 0.34958336 -0.56674004
		 0.34958336 -0.60293281 0.34958336 -0.63912559 0.34958336 -0.67531836 0.34958336 -0.71151102
		 0.34958336 0.012344226 0.31339061 -0.02384853 0.31339061 -0.060041286 0.31339061
		 -0.096234046 0.31339061 -0.1324268 0.31339061 -0.16861954 0.31339061 -0.20481232
		 0.31339061 -0.24100509 0.31339061 -0.27719784 0.31339061 -0.31339064 0.31339061 -0.34958339
		 0.31339061 -0.38577619 0.31339061 -0.42196894 0.31339061 -0.45816171 0.31339061 -0.49435449
		 0.31339061 -0.53054726 0.31339061 -0.56674004 0.31339061 -0.60293281 0.31339061 -0.63912559
		 0.31339061 -0.67531836 0.31339061 -0.71151102 0.31339061 0.012344226 0.27719778 -0.02384853
		 0.27719778 -0.060041286 0.27719778 -0.096234046 0.27719778 -0.1324268 0.27719778
		 -0.16861954 0.27719778 -0.20481232 0.27719778 -0.24100509 0.27719778 -0.27719784
		 0.27719778 -0.31339064 0.27719778 -0.34958339 0.27719778 -0.38577619 0.27719778 -0.42196894
		 0.27719778 -0.45816171 0.27719778 -0.49435449 0.27719778 -0.53054726 0.27719778 -0.56674004
		 0.27719778 -0.60293281 0.27719778 -0.63912559 0.27719778;
	setAttr ".uvtk[250:438]" -0.67531836 0.27719778 -0.71151102 0.27719778 0.012344226
		 0.24100506 -0.02384853 0.24100506 -0.060041286 0.24100506 -0.096234046 0.24100506
		 -0.1324268 0.24100506 -0.16861954 0.24100506 -0.20481232 0.24100506 -0.24100509 0.24100506
		 -0.27719784 0.24100506 -0.31339064 0.24100506 -0.34958339 0.24100506 -0.38577619
		 0.24100506 -0.42196894 0.24100506 -0.45816171 0.24100506 -0.49435449 0.24100506 -0.53054726
		 0.24100506 -0.56674004 0.24100506 -0.60293281 0.24100506 -0.63912559 0.24100506 -0.67531836
		 0.24100506 -0.71151102 0.24100506 0.012344226 0.20481223 -0.02384853 0.20481223 -0.060041286
		 0.20481223 -0.096234046 0.20481223 -0.1324268 0.20481223 -0.16861954 0.20481223 -0.20481232
		 0.20481223 -0.24100509 0.20481223 -0.27719784 0.20481223 -0.31339064 0.20481223 -0.34958339
		 0.20481223 -0.38577619 0.20481223 -0.42196894 0.20481223 -0.45816171 0.20481223 -0.49435449
		 0.20481223 -0.53054726 0.20481223 -0.56674004 0.20481223 -0.60293281 0.20481223 -0.63912559
		 0.20481223 -0.67531836 0.20481223 -0.71151102 0.20481223 0.012344226 0.16861951 -0.02384853
		 0.16861951 -0.060041286 0.16861951 -0.096234046 0.16861951 -0.1324268 0.16861951
		 -0.16861954 0.16861951 -0.20481232 0.16861951 -0.24100509 0.16861951 -0.27719784
		 0.16861951 -0.31339064 0.16861951 -0.34958339 0.16861951 -0.38577619 0.16861951 -0.42196894
		 0.16861951 -0.45816171 0.16861951 -0.49435449 0.16861951 -0.53054726 0.16861951 -0.56674004
		 0.16861951 -0.60293281 0.16861951 -0.63912559 0.16861951 -0.67531836 0.16861951 -0.71151102
		 0.16861951 0.012344226 0.13242674 -0.02384853 0.13242674 -0.060041286 0.13242674
		 -0.096234046 0.13242674 -0.1324268 0.13242674 -0.16861954 0.13242674 -0.20481232
		 0.13242674 -0.24100509 0.13242674 -0.27719784 0.13242674 -0.31339064 0.13242674 -0.34958339
		 0.13242674 -0.38577619 0.13242674 -0.42196894 0.13242674 -0.45816171 0.13242674 -0.49435449
		 0.13242674 -0.53054726 0.13242674 -0.56674004 0.13242674 -0.60293281 0.13242674 -0.63912559
		 0.13242674 -0.67531836 0.13242674 -0.71151102 0.13242674 0.012344226 0.096234024
		 -0.02384853 0.096234024 -0.060041286 0.096234024 -0.096234046 0.096234024 -0.1324268
		 0.096234024 -0.16861954 0.096234024 -0.20481232 0.096234024 -0.24100509 0.096234024
		 -0.27719784 0.096234024 -0.31339064 0.096234024 -0.34958339 0.096234024 -0.38577619
		 0.096234024 -0.42196894 0.096234024 -0.45816171 0.096234024 -0.49435449 0.096234024
		 -0.53054726 0.096234024 -0.56674004 0.096234024 -0.60293281 0.096234024 -0.63912559
		 0.096234024 -0.67531836 0.096234024 -0.71151102 0.096234024 0.012344226 0.060041249
		 -0.02384853 0.060041249 -0.060041286 0.060041249 -0.096234046 0.060041249 -0.1324268
		 0.060041249 -0.16861954 0.060041249 -0.20481232 0.060041249 -0.24100509 0.060041249
		 -0.27719784 0.060041249 -0.31339064 0.060041249 -0.34958339 0.060041249 -0.38577619
		 0.060041249 -0.42196894 0.060041249 -0.45816171 0.060041249 -0.49435449 0.060041249
		 -0.53054726 0.060041249 -0.56674004 0.060041249 -0.60293281 0.060041249 -0.63912559
		 0.060041249 -0.67531836 0.060041249 -0.71151102 0.060041249 0.012344226 0.023848474
		 -0.02384853 0.023848474 -0.060041286 0.023848474 -0.096234046 0.023848474 -0.1324268
		 0.023848474 -0.16861954 0.023848474 -0.20481232 0.023848474 -0.24100509 0.023848474
		 -0.27719784 0.023848474 -0.31339064 0.023848474 -0.34958339 0.023848474 -0.38577619
		 0.023848474 -0.42196894 0.023848474 -0.45816171 0.023848474 -0.49435449 0.023848474
		 -0.53054726 0.023848474 -0.56674004 0.023848474 -0.60293281 0.023848474 -0.63912559
		 0.023848474 -0.67531836 0.023848474 -0.71151102 0.023848474 -0.0057521546 0.7115109
		 -0.041944936 0.7115109 -0.078137666 0.7115109 -0.11433044 0.7115109 -0.15052322 0.7115109
		 -0.18671595 0.7115109 -0.22290872 0.7115109 -0.25910148 0.7115109 -0.29529423 0.7115109
		 -0.331487 0.7115109 -0.36767977 0.7115109 -0.40387249 0.7115109 -0.44006526 0.7115109
		 -0.47625801 0.7115109 -0.51245081 0.7115109 -0.54864359 0.7115109 -0.5848363 0.7115109
		 -0.62102914 0.7115109 -0.65722185 0.7115109 -0.69341463 0.7115109 -0.0057521546 -0.012344092
		 -0.041944936 -0.012344092 -0.078137666 -0.012344092 -0.11433044 -0.012344092 -0.15052322
		 -0.012344092 -0.18671595 -0.012344092 -0.22290872 -0.012344092 -0.25910148 -0.012344092
		 -0.29529423 -0.012344092 -0.331487 -0.012344092 -0.36767977 -0.012344092 -0.40387249
		 -0.012344092 -0.44006526 -0.012344092 -0.47625801 -0.012344092 -0.51245081 -0.012344092
		 -0.54864359 -0.012344092 -0.5848363 -0.012344092 -0.62102914 -0.012344092 -0.65722185
		 -0.012344092 -0.69341463 -0.012344092;
createNode polyTweakUV -n "polyTweakUV4";
	rename -uid "AAF471BC-4076-82B7-1B40-C1B90B549D24";
	setAttr ".uopa" yes;
	setAttr -s 439 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" 0.012344226 0.67531818 -0.02384853
		 0.67531818 -0.060041286 0.67531818 -0.096234046 0.67531818 -0.1324268 0.67531818
		 -0.16861954 0.67531818 -0.20481232 0.67531818 -0.24100509 0.67531818 -0.27719784
		 0.67531818 -0.31339064 0.67531818 -0.34958339 0.67531818 -0.38577619 0.67531818 -0.42196894
		 0.67531818 -0.45816171 0.67531818 -0.49435449 0.67531818 -0.53054726 0.67531818 -0.56674004
		 0.67531818 -0.60293281 0.67531818 -0.63912559 0.67531818 -0.67531836 0.67531818 -0.71151102
		 0.67531818 0.012344226 0.63912547 -0.02384853 0.63912547 -0.060041286 0.63912547
		 -0.096234046 0.63912547 -0.1324268 0.63912547 -0.16861954 0.63912547 -0.20481232
		 0.63912547 -0.24100509 0.63912547 -0.27719784 0.63912547 -0.31339064 0.63912547 -0.34958339
		 0.63912547 -0.38577619 0.63912547 -0.42196894 0.63912547 -0.45816171 0.63912547 -0.49435449
		 0.63912547 -0.53054726 0.63912547 -0.56674004 0.63912547 -0.60293281 0.63912547 -0.63912559
		 0.63912547 -0.67531836 0.63912547 -0.71151102 0.63912547 0.012344226 0.60293263 -0.02384853
		 0.60293263 -0.060041286 0.60293263 -0.096234046 0.60293263 -0.1324268 0.60293263
		 -0.16861954 0.60293263 -0.20481232 0.60293263 -0.24100509 0.60293263 -0.27719784
		 0.60293263 -0.31339064 0.60293263 -0.34958339 0.60293263 -0.38577619 0.60293263 -0.42196894
		 0.60293263 -0.45816171 0.60293263 -0.49435449 0.60293263 -0.53054726 0.60293263 -0.56674004
		 0.60293263 -0.60293281 0.60293263 -0.63912559 0.60293263 -0.67531836 0.60293263 -0.71151102
		 0.60293263 0.012344226 0.56673998 -0.02384853 0.56673998 -0.060041286 0.56673998
		 -0.096234046 0.56673998 -0.1324268 0.56673998 -0.16861954 0.56673998 -0.20481232
		 0.56673998 -0.24100509 0.56673998 -0.27719784 0.56673998 -0.31339064 0.56673998 -0.34958339
		 0.56673998 -0.38577619 0.56673998 -0.42196894 0.56673998 -0.45816171 0.56673998 -0.49435449
		 0.56673998 -0.53054726 0.56673998 -0.56674004 0.56673998 -0.60293281 0.56673998 -0.63912559
		 0.56673998 -0.67531836 0.56673998 -0.71151102 0.56673998 0.012344226 0.53054714 -0.02384853
		 0.53054714 -0.060041286 0.53054714 -0.096234046 0.53054714 -0.1324268 0.53054714
		 -0.16861954 0.53054714 -0.20481232 0.53054714 -0.24100509 0.53054714 -0.27719784
		 0.53054714 -0.31339064 0.53054714 -0.34958339 0.53054714 -0.38577619 0.53054714 -0.42196894
		 0.53054714 -0.45816171 0.53054714 -0.49435449 0.53054714 -0.53054726 0.53054714 -0.56674004
		 0.53054714 -0.60293281 0.53054714 -0.63912559 0.53054714 -0.67531836 0.53054714 -0.71151102
		 0.53054714 0.012344226 0.4943544 -0.02384853 0.4943544 -0.060041286 0.4943544 -0.096234046
		 0.4943544 -0.1324268 0.4943544 -0.16861954 0.4943544 -0.20481232 0.4943544 -0.24100509
		 0.4943544 -0.27719784 0.4943544 -0.31339064 0.4943544 -0.34958339 0.4943544 -0.38577619
		 0.4943544 -0.42196894 0.4943544 -0.45816171 0.4943544 -0.49435449 0.4943544 -0.53054726
		 0.4943544 -0.56674004 0.4943544 -0.60293281 0.4943544 -0.63912559 0.4943544 -0.67531836
		 0.4943544 -0.71151102 0.4943544 0.012344226 0.45816162 -0.02384853 0.45816162 -0.060041286
		 0.45816162 -0.096234046 0.45816162 -0.1324268 0.45816162 -0.16861954 0.45816162 -0.20481232
		 0.45816162 -0.24100509 0.45816162 -0.27719784 0.45816162 -0.31339064 0.45816162 -0.34958339
		 0.45816162 -0.38577619 0.45816162 -0.42196894 0.45816162 -0.45816171 0.45816162 -0.49435449
		 0.45816162 -0.53054726 0.45816162 -0.56674004 0.45816162 -0.60293281 0.45816162 -0.63912559
		 0.45816162 -0.67531836 0.45816162 -0.71151102 0.45816162 0.012344226 0.42196891 -0.02384853
		 0.42196891 -0.060041286 0.42196891 -0.096234046 0.42196891 -0.1324268 0.42196891
		 -0.16861954 0.42196891 -0.20481232 0.42196891 -0.24100509 0.42196891 -0.27719784
		 0.42196891 -0.31339064 0.42196891 -0.34958339 0.42196891 -0.38577619 0.42196891 -0.42196894
		 0.42196891 -0.45816171 0.42196891 -0.49435449 0.42196891 -0.53054726 0.42196891 -0.56674004
		 0.42196891 -0.60293281 0.42196891 -0.63912559 0.42196891 -0.67531836 0.42196891 -0.71151102
		 0.42196891 0.012344226 0.38577619 -0.02384853 0.38577619 -0.060041286 0.38577619
		 -0.096234046 0.38577619 -0.1324268 0.38577619 -0.16861954 0.38577619 -0.20481232
		 0.38577619 -0.24100509 0.38577619 -0.27719784 0.38577619 -0.31339064 0.38577619 -0.34958339
		 0.38577619 -0.38577619 0.38577619 -0.42196894 0.38577619 -0.45816171 0.38577619 -0.49435449
		 0.38577619 -0.53054726 0.38577619 -0.56674004 0.38577619 -0.60293281 0.38577619 -0.63912559
		 0.38577619 -0.67531836 0.38577619 -0.71151102 0.38577619 0.012344226 0.34958336 -0.02384853
		 0.34958336 -0.060041286 0.34958336 -0.096234046 0.34958336 -0.1324268 0.34958336
		 -0.16861954 0.34958336 -0.20481232 0.34958336 -0.24100509 0.34958336 -0.27719784
		 0.34958336 -0.31339064 0.34958336 -0.34958339 0.34958336 -0.38577619 0.34958336 -0.42196894
		 0.34958336 -0.45816171 0.34958336 -0.49435449 0.34958336 -0.53054726 0.34958336 -0.56674004
		 0.34958336 -0.60293281 0.34958336 -0.63912559 0.34958336 -0.67531836 0.34958336 -0.71151102
		 0.34958336 0.012344226 0.31339061 -0.02384853 0.31339061 -0.060041286 0.31339061
		 -0.096234046 0.31339061 -0.1324268 0.31339061 -0.16861954 0.31339061 -0.20481232
		 0.31339061 -0.24100509 0.31339061 -0.27719784 0.31339061 -0.31339064 0.31339061 -0.34958339
		 0.31339061 -0.38577619 0.31339061 -0.42196894 0.31339061 -0.45816171 0.31339061 -0.49435449
		 0.31339061 -0.53054726 0.31339061 -0.56674004 0.31339061 -0.60293281 0.31339061 -0.63912559
		 0.31339061 -0.67531836 0.31339061 -0.71151102 0.31339061 0.012344226 0.27719778 -0.02384853
		 0.27719778 -0.060041286 0.27719778 -0.096234046 0.27719778 -0.1324268 0.27719778
		 -0.16861954 0.27719778 -0.20481232 0.27719778 -0.24100509 0.27719778 -0.27719784
		 0.27719778 -0.31339064 0.27719778 -0.34958339 0.27719778 -0.38577619 0.27719778 -0.42196894
		 0.27719778 -0.45816171 0.27719778 -0.49435449 0.27719778 -0.53054726 0.27719778 -0.56674004
		 0.27719778 -0.60293281 0.27719778 -0.63912559 0.27719778;
	setAttr ".uvtk[250:438]" -0.67531836 0.27719778 -0.71151102 0.27719778 0.012344226
		 0.24100506 -0.02384853 0.24100506 -0.060041286 0.24100506 -0.096234046 0.24100506
		 -0.1324268 0.24100506 -0.16861954 0.24100506 -0.20481232 0.24100506 -0.24100509 0.24100506
		 -0.27719784 0.24100506 -0.31339064 0.24100506 -0.34958339 0.24100506 -0.38577619
		 0.24100506 -0.42196894 0.24100506 -0.45816171 0.24100506 -0.49435449 0.24100506 -0.53054726
		 0.24100506 -0.56674004 0.24100506 -0.60293281 0.24100506 -0.63912559 0.24100506 -0.67531836
		 0.24100506 -0.71151102 0.24100506 0.012344226 0.20481223 -0.02384853 0.20481223 -0.060041286
		 0.20481223 -0.096234046 0.20481223 -0.1324268 0.20481223 -0.16861954 0.20481223 -0.20481232
		 0.20481223 -0.24100509 0.20481223 -0.27719784 0.20481223 -0.31339064 0.20481223 -0.34958339
		 0.20481223 -0.38577619 0.20481223 -0.42196894 0.20481223 -0.45816171 0.20481223 -0.49435449
		 0.20481223 -0.53054726 0.20481223 -0.56674004 0.20481223 -0.60293281 0.20481223 -0.63912559
		 0.20481223 -0.67531836 0.20481223 -0.71151102 0.20481223 0.012344226 0.16861951 -0.02384853
		 0.16861951 -0.060041286 0.16861951 -0.096234046 0.16861951 -0.1324268 0.16861951
		 -0.16861954 0.16861951 -0.20481232 0.16861951 -0.24100509 0.16861951 -0.27719784
		 0.16861951 -0.31339064 0.16861951 -0.34958339 0.16861951 -0.38577619 0.16861951 -0.42196894
		 0.16861951 -0.45816171 0.16861951 -0.49435449 0.16861951 -0.53054726 0.16861951 -0.56674004
		 0.16861951 -0.60293281 0.16861951 -0.63912559 0.16861951 -0.67531836 0.16861951 -0.71151102
		 0.16861951 0.012344226 0.13242674 -0.02384853 0.13242674 -0.060041286 0.13242674
		 -0.096234046 0.13242674 -0.1324268 0.13242674 -0.16861954 0.13242674 -0.20481232
		 0.13242674 -0.24100509 0.13242674 -0.27719784 0.13242674 -0.31339064 0.13242674 -0.34958339
		 0.13242674 -0.38577619 0.13242674 -0.42196894 0.13242674 -0.45816171 0.13242674 -0.49435449
		 0.13242674 -0.53054726 0.13242674 -0.56674004 0.13242674 -0.60293281 0.13242674 -0.63912559
		 0.13242674 -0.67531836 0.13242674 -0.71151102 0.13242674 0.012344226 0.096234024
		 -0.02384853 0.096234024 -0.060041286 0.096234024 -0.096234046 0.096234024 -0.1324268
		 0.096234024 -0.16861954 0.096234024 -0.20481232 0.096234024 -0.24100509 0.096234024
		 -0.27719784 0.096234024 -0.31339064 0.096234024 -0.34958339 0.096234024 -0.38577619
		 0.096234024 -0.42196894 0.096234024 -0.45816171 0.096234024 -0.49435449 0.096234024
		 -0.53054726 0.096234024 -0.56674004 0.096234024 -0.60293281 0.096234024 -0.63912559
		 0.096234024 -0.67531836 0.096234024 -0.71151102 0.096234024 0.012344226 0.060041249
		 -0.02384853 0.060041249 -0.060041286 0.060041249 -0.096234046 0.060041249 -0.1324268
		 0.060041249 -0.16861954 0.060041249 -0.20481232 0.060041249 -0.24100509 0.060041249
		 -0.27719784 0.060041249 -0.31339064 0.060041249 -0.34958339 0.060041249 -0.38577619
		 0.060041249 -0.42196894 0.060041249 -0.45816171 0.060041249 -0.49435449 0.060041249
		 -0.53054726 0.060041249 -0.56674004 0.060041249 -0.60293281 0.060041249 -0.63912559
		 0.060041249 -0.67531836 0.060041249 -0.71151102 0.060041249 0.012344226 0.023848474
		 -0.02384853 0.023848474 -0.060041286 0.023848474 -0.096234046 0.023848474 -0.1324268
		 0.023848474 -0.16861954 0.023848474 -0.20481232 0.023848474 -0.24100509 0.023848474
		 -0.27719784 0.023848474 -0.31339064 0.023848474 -0.34958339 0.023848474 -0.38577619
		 0.023848474 -0.42196894 0.023848474 -0.45816171 0.023848474 -0.49435449 0.023848474
		 -0.53054726 0.023848474 -0.56674004 0.023848474 -0.60293281 0.023848474 -0.63912559
		 0.023848474 -0.67531836 0.023848474 -0.71151102 0.023848474 -0.0057521546 0.7115109
		 -0.041944936 0.7115109 -0.078137666 0.7115109 -0.11433044 0.7115109 -0.15052322 0.7115109
		 -0.18671595 0.7115109 -0.22290872 0.7115109 -0.25910148 0.7115109 -0.29529423 0.7115109
		 -0.331487 0.7115109 -0.36767977 0.7115109 -0.40387249 0.7115109 -0.44006526 0.7115109
		 -0.47625801 0.7115109 -0.51245081 0.7115109 -0.54864359 0.7115109 -0.5848363 0.7115109
		 -0.62102914 0.7115109 -0.65722185 0.7115109 -0.69341463 0.7115109 -0.0057521546 -0.012344092
		 -0.041944936 -0.012344092 -0.078137666 -0.012344092 -0.11433044 -0.012344092 -0.15052322
		 -0.012344092 -0.18671595 -0.012344092 -0.22290872 -0.012344092 -0.25910148 -0.012344092
		 -0.29529423 -0.012344092 -0.331487 -0.012344092 -0.36767977 -0.012344092 -0.40387249
		 -0.012344092 -0.44006526 -0.012344092 -0.47625801 -0.012344092 -0.51245081 -0.012344092
		 -0.54864359 -0.012344092 -0.5848363 -0.012344092 -0.62102914 -0.012344092 -0.65722185
		 -0.012344092 -0.69341463 -0.012344092;
createNode polyTweakUV -n "polyTweakUV5";
	rename -uid "D7D59D7F-4338-D94F-5E8A-1FB0496B118B";
	setAttr ".uopa" yes;
	setAttr -s 223 ".uvtk[0:222]" -type "float2" 0.052279569 -0.0099182576
		 0.02360341 -0.0099182576 -0.0050726533 -0.0099182576 -0.033748791 -0.0099182576 -0.062424906
		 -0.0099182576 -0.091101021 -0.0099182576 -0.11977711 -0.0099182576 -0.14845318 -0.0099182576
		 -0.17712936 -0.0099182576 -0.20580545 -0.0099182576 -0.23448151 -0.0099182576 -0.26315761
		 -0.0099182576 -0.29183382 -0.0099182576 -0.32050985 -0.0099182576 -0.349186 -0.0099182576
		 0.052279569 -0.038594417 0.02360341 -0.038594417 -0.0050726533 -0.038594417 -0.033748791
		 -0.038594417 -0.062424906 -0.038594417 -0.091101021 -0.038594417 -0.11977711 -0.038594417
		 -0.14845318 -0.038594417 -0.17712936 -0.038594417 -0.20580545 -0.038594417 -0.23448151
		 -0.038594417 -0.26315761 -0.038594417 -0.29183382 -0.038594417 -0.32050985 -0.038594417
		 -0.349186 -0.038594417 0.052279569 -0.067270495 0.02360341 -0.067270495 -0.0050726533
		 -0.067270495 -0.033748791 -0.067270495 -0.062424906 -0.067270495 -0.091101021 -0.067270495
		 -0.11977711 -0.067270495 -0.14845318 -0.067270495 -0.17712936 -0.067270495 -0.20580545
		 -0.067270495 -0.23448151 -0.067270495 -0.26315761 -0.067270495 -0.29183382 -0.067270495
		 -0.32050985 -0.067270495 -0.349186 -0.067270495 0.052279569 -0.095946617 0.02360341
		 -0.095946617 -0.0050726533 -0.095946617 -0.033748791 -0.095946617 -0.062424906 -0.095946617
		 -0.091101021 -0.095946617 -0.11977711 -0.095946617 -0.14845318 -0.095946617 -0.17712936
		 -0.095946617 -0.20580545 -0.095946617 -0.23448151 -0.095946617 -0.26315761 -0.095946617
		 -0.29183382 -0.095946617 -0.32050985 -0.095946617 -0.349186 -0.095946617 0.052279569
		 -0.12462271 0.02360341 -0.12462271 -0.0050726533 -0.12462271 -0.033748791 -0.12462271
		 -0.062424906 -0.12462271 -0.091101021 -0.12462271 -0.11977711 -0.12462271 -0.14845318
		 -0.12462271 -0.17712936 -0.12462271 -0.20580545 -0.12462271 -0.23448151 -0.12462271
		 -0.26315761 -0.12462271 -0.29183382 -0.12462271 -0.32050985 -0.12462271 -0.349186
		 -0.12462271 0.052279569 -0.15329883 0.02360341 -0.15329883 -0.0050726533 -0.15329883
		 -0.033748791 -0.15329883 -0.062424906 -0.15329883 -0.091101021 -0.15329883 -0.11977711
		 -0.15329883 -0.14845318 -0.15329883 -0.17712936 -0.15329883 -0.20580545 -0.15329883
		 -0.23448151 -0.15329883 -0.26315761 -0.15329883 -0.29183382 -0.15329883 -0.32050985
		 -0.15329883 -0.349186 -0.15329883 0.052279569 -0.18197492 0.02360341 -0.18197492
		 -0.0050726533 -0.18197492 -0.033748791 -0.18197492 -0.062424906 -0.18197492 -0.091101021
		 -0.18197492 -0.11977711 -0.18197492 -0.14845318 -0.18197492 -0.17712936 -0.18197492
		 -0.20580545 -0.18197492 -0.23448151 -0.18197492 -0.26315761 -0.18197492 -0.29183382
		 -0.18197492 -0.32050985 -0.18197492 -0.349186 -0.18197492 0.052279569 -0.21065101
		 0.02360341 -0.21065101 -0.0050726533 -0.21065101 -0.033748791 -0.21065101 -0.062424906
		 -0.21065101 -0.091101021 -0.21065101 -0.11977711 -0.21065101 -0.14845318 -0.21065101
		 -0.17712936 -0.21065101 -0.20580545 -0.21065101 -0.23448151 -0.21065101 -0.26315761
		 -0.21065101 -0.29183382 -0.21065101 -0.32050985 -0.21065101 -0.349186 -0.21065101
		 0.052279569 -0.2393271 0.02360341 -0.2393271 -0.0050726533 -0.2393271 -0.033748791
		 -0.2393271 -0.062424906 -0.2393271 -0.091101021 -0.2393271 -0.11977711 -0.2393271
		 -0.14845318 -0.2393271 -0.17712936 -0.2393271 -0.20580545 -0.2393271 -0.23448151
		 -0.2393271 -0.26315761 -0.2393271 -0.29183382 -0.2393271 -0.32050985 -0.2393271 -0.349186
		 -0.2393271 0.052279569 -0.26800326 0.02360341 -0.26800326 -0.0050726533 -0.26800326
		 -0.033748791 -0.26800326 -0.062424906 -0.26800326 -0.091101021 -0.26800326 -0.11977711
		 -0.26800326 -0.14845318 -0.26800326 -0.17712936 -0.26800326 -0.20580545 -0.26800326
		 -0.23448151 -0.26800326 -0.26315761 -0.26800326 -0.29183382 -0.26800326 -0.32050985
		 -0.26800326 -0.349186 -0.26800326 0.052279569 -0.29667935 0.02360341 -0.29667935
		 -0.0050726533 -0.29667935 -0.033748791 -0.29667935 -0.062424906 -0.29667935 -0.091101021
		 -0.29667935 -0.11977711 -0.29667935 -0.14845318 -0.29667935 -0.17712936 -0.29667935
		 -0.20580545 -0.29667935 -0.23448151 -0.29667935 -0.26315761 -0.29667935 -0.29183382
		 -0.29667935 -0.32050985 -0.29667935 -0.349186 -0.29667935 0.052279569 -0.3253555
		 0.02360341 -0.3253555 -0.0050726533 -0.3253555 -0.033748791 -0.3253555 -0.062424906
		 -0.3253555 -0.091101021 -0.3253555 -0.11977711 -0.3253555 -0.14845318 -0.3253555
		 -0.17712936 -0.3253555 -0.20580545 -0.3253555 -0.23448151 -0.3253555 -0.26315761
		 -0.3253555 -0.29183382 -0.3253555 -0.32050985 -0.3253555 -0.349186 -0.3253555 0.052279569
		 -0.35403159 0.02360341 -0.35403159 -0.0050726533 -0.35403159 -0.033748791 -0.35403159
		 -0.062424906 -0.35403159 -0.091101021 -0.35403159 -0.11977711 -0.35403159 -0.14845318
		 -0.35403159 -0.17712936 -0.35403159 -0.20580545 -0.35403159 -0.23448151 -0.35403159
		 -0.26315761 -0.35403159 -0.29183382 -0.35403159 -0.32050985 -0.35403159 -0.349186
		 -0.35403159 0.037941568 0.018757813 0.0092653707 0.018757813 -0.019410685 0.018757813
		 -0.048086829 0.018757813 -0.07676293 0.018757813 -0.10543907 0.018757813 -0.13411516
		 0.018757813 -0.16279128 0.018757813 -0.19146737 0.018757813 -0.22014347 0.018757813
		 -0.24881965 0.018757813 -0.27749568 0.018757813 -0.30617177 0.018757813 -0.33484787
		 0.018757813 0.037941568 -0.38270763 0.0092653707 -0.38270763 -0.019410685 -0.38270763
		 -0.048086829 -0.38270763 -0.07676293 -0.38270763 -0.10543907 -0.38270763 -0.13411516
		 -0.38270763 -0.16279128 -0.38270763 -0.19146737 -0.38270763 -0.22014347 -0.38270763
		 -0.24881965 -0.38270763 -0.27749568 -0.38270763 -0.30617177 -0.38270763 -0.33484787
		 -0.38270763;
createNode polyTweakUV -n "polyTweakUV6";
	rename -uid "E1125474-4C08-1C0A-B032-C6AE66C520B9";
	setAttr ".uopa" yes;
	setAttr -s 210 ".uvtk[0:209]" -type "float2" 0.31256524 0.0092243254 0.31308731
		 0.010249212 0.31390068 0.011062577 0.31492558 0.011584759 0.31606171 0.01176469 0.31719771
		 0.011584774 0.31822267 0.011062548 0.31903592 0.010249183 0.31955823 0.0092243403
		 0.31973818 0.0080882311 0.31955823 0.0069521219 0.31903592 0.0059272647 0.31822255
		 0.0051138997 0.31719771 0.0045917034 0.31606171 0.004411757 0.31492564 0.0045917034
		 0.31390062 0.0051138997 0.31308725 0.0059272647 0.31256518 0.0069521368 0.31238529
		 0.0080882311 0.31900296 0.004411757 0.31870881 0.004411757 0.31841466 0.004411757
		 0.31812063 0.004411757 0.3178263 0.004411757 0.31753233 0.004411757 0.31723818 0.004411757
		 0.31694397 0.004411757 0.31664982 0.004411757 0.31635579 0.004411757 0.31606171 0.004411757
		 0.31576762 0.004411757 0.31547335 0.004411757 0.31517932 0.004411757 0.31488523 0.004411757
		 0.3145912 0.004411757 0.31429687 0.004411757 0.31400302 0.004411757 0.31370875 0.004411757
		 0.31341472 0.004411757 0.31312057 0.004411757 0.31900296 -0.0044338703 0.31870881
		 -0.0044338703 0.31841466 -0.0044338703 0.31812063 -0.0044338703 0.3178263 -0.0044338703
		 0.31753233 -0.0044338703 0.31723818 -0.0044338703 0.31694397 -0.0044338703 0.31664982
		 -0.0044338703 0.31635579 -0.0044338703 0.31606171 -0.0044338703 0.31576762 -0.0044338703
		 0.31547335 -0.0044338703 0.31517932 -0.0044338703 0.31488523 -0.0044338703 0.3145912
		 -0.0044338703 0.31429687 -0.0044338703 0.31400302 -0.0044338703 0.31370875 -0.0044338703
		 0.31341472 -0.0044338703 0.31312057 -0.0044338703 0.31256524 -0.0069521666 0.31308731
		 -0.0059272647 0.31390068 -0.0051138997 0.31492558 -0.0045917034 0.31606171 -0.004411757
		 0.31719771 -0.0045917034 0.31822267 -0.0051138997 0.31903592 -0.0059272647 0.31955823
		 -0.0069521666 0.31973818 -0.0080882311 0.31955823 -0.0092242956 0.31903592 -0.010249197
		 0.31822255 -0.011062562 0.31719771 -0.011584759 0.31606171 -0.011764765 0.31492564
		 -0.011584759 0.31390062 -0.011062562 0.31308725 -0.010249197 0.31256518 -0.0092242956
		 0.31238529 -0.0080882311 0.31606171 0.0082353055 0.31606171 -0.0079411864 0.31312063
		 0.0026670098 0.31900296 0.0026670098 0.31870881 0.0026732683 0.31841466 0.0026782155
		 0.31812063 0.0026813745 0.3178263 0.0026824474 0.31753233 0.0026813745 0.31723818
		 0.0026782155 0.31694397 0.0026732683 0.31664988 0.0026670098 0.31635579 0.0026601255
		 0.31606171 0.0026532114 0.31576762 0.0026469827 0.31547335 0.0026420653 0.31517932
		 0.0026388764 0.31488523 0.0026378036 0.3145912 0.0026388764 0.31429687 0.0026420653
		 0.31400302 0.0026469827 0.31370875 0.0026532114 0.31341472 0.0026601255 0.31312057
		 -0.00049334764 0.31900296 -0.00049334764 0.31870881 -0.00017434359 0.31841466 0.00011655688
		 0.31812063 0.00032448769 0.3178263 0.00040045381 0.31753221 0.00032448769 0.31723818
		 0.00011655688 0.31694397 -0.00017434359 0.31664988 -0.00049334764 0.31635579 -0.00079703331
		 0.31606171 -0.0010587573 0.31576762 -0.0012655854 0.31547335 -0.0014132261 0.31517932
		 -0.0015012622 0.31488523 -0.0015305281 0.3145912 -0.0015012622 0.31429687 -0.0014132261
		 0.31400302 -0.0012655854 0.31370875 -0.0010587573 0.31341466 -0.00079703331 0.31312057
		 0.00028085709 0.31900296 0.00028085709 0.31870881 0.000544101 0.31841466 0.00077858567
		 0.31812063 0.00094327331 0.3178263 0.001002878 0.31753233 0.00094327331 0.31723818
		 0.00077858567 0.31694397 0.000544101 0.31664988 0.00028085709 0.31635579 2.3514032e-005
		 0.31606171 -0.00020426512 0.31576762 -0.0003888011 0.31547335 -0.00052314997 0.31517932
		 -0.0006043911 0.31488523 -0.00063151121 0.3145912 -0.0006043911 0.31429687 -0.00052314997
		 0.31400302 -0.0003888011 0.31370875 -0.00020426512 0.31341466 2.3514032e-005 0.31312057
		 0.0010770857 0.31900296 0.0010770857 0.31870881 0.0012834966 0.31841466 0.001460284
		 0.31812063 0.0015806556 0.3178263 0.0016235113 0.31753233 0.0015806556 0.31723818
		 0.001460284 0.31694397 0.0012834966 0.31664988 0.0010770857 0.31635579 0.00086674094
		 0.31606171 0.00067305565 0.31576762 0.00051084161 0.31547335 0.00038963556 0.31517932
		 0.00031501055 0.31488523 0.00028985739 0.3145912 0.00031501055 0.31429687 0.00038963556
		 0.31400302 0.00051084161 0.31370875 0.00067305565 0.31341466 0.00086674094 0.31312057
		 0.0018740594 0.31900296 0.0018740594 0.31870881 0.0020234883 0.31841466 0.0021424592
		 0.31812063 0.0022184551 0.3178263 0.0022445023 0.31753233 0.0022184551 0.31723818
		 0.0021424592 0.31694397 0.0020234883 0.31664988 0.0018740296 0.31635579 0.0017108023
		 0.31606171 0.0015514493 0.31576762 0.0014116466 0.31547335 0.0013036728 0.31517932
		 0.0012357533 0.31488523 0.0012125969 0.3145912 0.0012357235 0.31429687 0.0013036728
		 0.31400302 0.0014116466 0.31370875 0.0015514493 0.31341466 0.0017108023 0.31312057
		 0.0035797358 0.31900296 0.0035797358 0.31870881 0.003565371 0.31841466 0.0035524666
		 0.31812063 0.0035433769 0.3178263 0.0035400987 0.31753233 0.0035433769 0.31723818
		 0.0035524666 0.31694397 0.003565371 0.31664982 0.0035797358 0.31635579 0.0035936534
		 0.31606171 0.0036056936 0.31576762 0.0036152899 0.31547335 0.0036220849 0.31517932
		 0.0036261678 0.31488523 0.0036275089 0.3145912 0.0036261678 0.31429687 0.0036220849
		 0.31400302 0.0036152899 0.31370875 0.0036056936 0.31341472 0.0035936534;
createNode shadingEngine -n "phong1SG";
	rename -uid "F44EE1B3-47EC-748A-6953-1184C58C5136";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
	rename -uid "7D99AF1F-44F7-70AC-4C2B-F0949828FAE2";
createNode checker -n "checker1";
	rename -uid "EFE3764D-4207-CC17-6AE3-C08A87BC9CE5";
createNode place2dTexture -n "place2dTexture1";
	rename -uid "60A9EDDC-4FE9-4C2D-8097-C899FA844AA2";
	setAttr ".re" -type "float2" 4 4 ;
createNode shadingEngine -n "lambert3SG";
	rename -uid "8974B6FF-48F9-4FE0-A01E-6084D630296F";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
	rename -uid "4AA0A92F-461C-5D73-C170-858365F184A7";
createNode file -n "file1";
	rename -uid "65AE91E1-4506-3174-165E-BBBE0154FE13";
	setAttr ".ftn" -type "string" "C:/Users/game115/Desktop/PCå¥êl return/PCgenjin_enemy_uv.jpg";
	setAttr ".cs" -type "string" "sRGB";
createNode place2dTexture -n "place2dTexture2";
	rename -uid "E49A8A1E-4D38-4ECE-52A4-D093F932E4B4";
createNode nodeGraphEditorInfo -n "hyperShadePrimaryNodeEditorSavedTabsInfo";
	rename -uid "49D13214-42C5-4A10-99E6-089B20A4443F";
	setAttr ".tgi[0].tn" -type "string" "Untitled_1";
	setAttr ".tgi[0].vl" -type "double2" -636.30949852485605 13.690475646465563 ;
	setAttr ".tgi[0].vh" -type "double2" -480.35712376946577 397.02379374750137 ;
	setAttr -s 3 ".tgi[0].ni";
	setAttr ".tgi[0].ni[0].x" 1.4285714626312256;
	setAttr ".tgi[0].ni[0].y" -20;
	setAttr ".tgi[0].ni[0].nvs" 1923;
	setAttr ".tgi[0].ni[1].x" 262.85714721679687;
	setAttr ".tgi[0].ni[1].y" -68.571426391601563;
	setAttr ".tgi[0].ni[1].nvs" 2147;
	setAttr ".tgi[0].ni[2].x" 262.85714721679687;
	setAttr ".tgi[0].ni[2].y" -1.4285714626312256;
	setAttr ".tgi[0].ni[2].nvs" 1923;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -s 4 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :lambert1;
select -ne :initialShadingGroup;
	setAttr -s 14 ".dsm";
	setAttr ".ro" yes;
	setAttr -s 8 ".gn";
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :initialMaterialInfo;
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
connectAttr "polyTweakUV6.out" "pCylinderShape1.i";
connectAttr "polyTweakUV6.uvtk[0]" "pCylinderShape1.uvst[0].uvtw";
connectAttr "polyTweakUV2.out" "pSphereShape1.i";
connectAttr "polyTweakUV2.uvtk[0]" "pSphereShape1.uvst[0].uvtw";
connectAttr "polyTweakUV3.out" "pSphereShape2.i";
connectAttr "polyTweakUV3.uvtk[0]" "pSphereShape2.uvst[0].uvtw";
connectAttr "polyTweakUV5.out" "pSphereShape3.i";
connectAttr "polyTweakUV5.uvtk[0]" "pSphereShape3.uvst[0].uvtw";
connectAttr "groupId3.id" "pSphereShape4.iog.og[0].gid";
connectAttr ":initialShadingGroup.mwc" "pSphereShape4.iog.og[0].gco";
connectAttr "groupParts2.og" "pSphereShape4.i";
connectAttr "groupId4.id" "pSphereShape4.ciog.cog[0].cgid";
connectAttr "groupId1.id" "pCylinderShape2.iog.og[0].gid";
connectAttr ":initialShadingGroup.mwc" "pCylinderShape2.iog.og[0].gco";
connectAttr "groupParts1.og" "pCylinderShape2.i";
connectAttr "groupId2.id" "pCylinderShape2.ciog.cog[0].cgid";
connectAttr "groupId7.id" "pSphereShape5.iog.og[0].gid";
connectAttr ":initialShadingGroup.mwc" "pSphereShape5.iog.og[0].gco";
connectAttr "groupParts4.og" "pSphereShape5.i";
connectAttr "groupId8.id" "pSphereShape5.ciog.cog[0].cgid";
connectAttr "groupId5.id" "pCylinderShape3.iog.og[0].gid";
connectAttr ":initialShadingGroup.mwc" "pCylinderShape3.iog.og[0].gco";
connectAttr "groupParts3.og" "pCylinderShape3.i";
connectAttr "groupId6.id" "pCylinderShape3.ciog.cog[0].cgid";
connectAttr "polyTweakUV4.out" "pSphereShape6.i";
connectAttr "polyTweakUV4.uvtk[0]" "pSphereShape6.uvst[0].uvtw";
connectAttr "polyTweakUV1.out" "pSphereShape7.i";
connectAttr "polyTweakUV1.uvtk[0]" "pSphereShape7.uvst[0].uvtw";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "phong1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "lambert3SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "phong1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "lambert3SG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "polyCylinder1.out" "polyCut1.ip";
connectAttr "pCylinderShape1.wm" "polyCut1.mp";
connectAttr "polyTweak1.out" "polyCut2.ip";
connectAttr "pCylinderShape1.wm" "polyCut2.mp";
connectAttr "polyCut1.out" "polyTweak1.ip";
connectAttr "polyTweak2.out" "polyCut3.ip";
connectAttr "pCylinderShape1.wm" "polyCut3.mp";
connectAttr "polyCut2.out" "polyTweak2.ip";
connectAttr "polyCut3.out" "polyCut4.ip";
connectAttr "pCylinderShape1.wm" "polyCut4.mp";
connectAttr "polyCut4.out" "polyCut5.ip";
connectAttr "pCylinderShape1.wm" "polyCut5.mp";
connectAttr "polyTweak3.out" "polyCut6.ip";
connectAttr "pCylinderShape1.wm" "polyCut6.mp";
connectAttr "polyCut5.out" "polyTweak3.ip";
connectAttr "polyCylinder2.out" "groupParts1.ig";
connectAttr "groupId1.id" "groupParts1.gi";
connectAttr "polySphere4.out" "groupParts2.ig";
connectAttr "groupId3.id" "groupParts2.gi";
connectAttr "polyCylinder3.out" "groupParts3.ig";
connectAttr "groupId5.id" "groupParts3.gi";
connectAttr "polySphere5.out" "groupParts4.ig";
connectAttr "groupId7.id" "groupParts4.gi";
connectAttr "polySphere7.out" "polyTweakUV1.ip";
connectAttr "polySphere1.out" "polyTweakUV2.ip";
connectAttr "polySphere2.out" "polyTweakUV3.ip";
connectAttr "polySphere6.out" "polyTweakUV4.ip";
connectAttr "polySphere3.out" "polyTweakUV5.ip";
connectAttr "polyCut6.out" "polyTweakUV6.ip";
connectAttr "phong1SG.msg" "materialInfo1.sg";
connectAttr "place2dTexture1.o" "checker1.uv";
connectAttr "place2dTexture1.ofs" "checker1.fs";
connectAttr "lambert3SG.msg" "materialInfo2.sg";
connectAttr ":defaultColorMgtGlobals.cme" "file1.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "file1.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "file1.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "file1.ws";
connectAttr "place2dTexture2.c" "file1.c";
connectAttr "place2dTexture2.tf" "file1.tf";
connectAttr "place2dTexture2.rf" "file1.rf";
connectAttr "place2dTexture2.mu" "file1.mu";
connectAttr "place2dTexture2.mv" "file1.mv";
connectAttr "place2dTexture2.s" "file1.s";
connectAttr "place2dTexture2.wu" "file1.wu";
connectAttr "place2dTexture2.wv" "file1.wv";
connectAttr "place2dTexture2.re" "file1.re";
connectAttr "place2dTexture2.of" "file1.of";
connectAttr "place2dTexture2.r" "file1.ro";
connectAttr "place2dTexture2.n" "file1.n";
connectAttr "place2dTexture2.vt1" "file1.vt1";
connectAttr "place2dTexture2.vt2" "file1.vt2";
connectAttr "place2dTexture2.vt3" "file1.vt3";
connectAttr "place2dTexture2.vc1" "file1.vc1";
connectAttr "place2dTexture2.o" "file1.uv";
connectAttr "place2dTexture2.ofs" "file1.fs";
connectAttr "place2dTexture2.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[0].dn"
		;
connectAttr "lambert3SG.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[1].dn"
		;
connectAttr "file1.msg" "hyperShadePrimaryNodeEditorSavedTabsInfo.tgi[0].ni[2].dn"
		;
connectAttr "phong1SG.pa" ":renderPartition.st" -na;
connectAttr "lambert3SG.pa" ":renderPartition.st" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "checker1.msg" ":defaultTextureList1.tx" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "file1.oc" ":lambert1.c";
connectAttr "pCylinderShape2.iog.og[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pCylinderShape2.ciog.cog[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape4.iog.og[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape4.ciog.cog[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pCylinderShape3.iog.og[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pCylinderShape3.ciog.cog[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape5.iog.og[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape5.ciog.cog[0]" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape7.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape6.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape3.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape2.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pSphereShape1.iog" ":initialShadingGroup.dsm" -na;
connectAttr "pCylinderShape1.iog" ":initialShadingGroup.dsm" -na;
connectAttr "groupId1.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId2.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId3.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId4.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId5.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId6.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId7.msg" ":initialShadingGroup.gn" -na;
connectAttr "groupId8.msg" ":initialShadingGroup.gn" -na;
connectAttr "file1.msg" ":initialMaterialInfo.t" -na;
connectAttr "file1.oc" ":internal_standInShader.ic";
// End of PCgenjin_enemy.ma
