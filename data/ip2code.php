<?php
$zipcode = file('codeList.txt');
$cityMap  = array();
$provinceMap = array();
$countryMap = array();

$defulatMap = file('blackdefault.txt');
foreach ($defulatMap as $k => $v) {
	$defulatMap[$k] = trim($v);
}

foreach ($zipcode as $codeStr) {
	list($code, $address) = explode("\t", $codeStr);
	$code = trim($code);
	$address = str_replace(array('特别行政区', '市', '省', '回族自治区', '壮族自治区', '自治区', '维吾尔'), '', trim($address));
	list($country, $province, $city) = explode('->', $address);
	$countryMap[$country] = substr($code, 0, 3) . '00000';

	$chinaFlag = substr($code, 0, 3);
	$provinceFlag = substr($code, -3);
	if ($provinceFlag == '000' && $chinaFlag== '156') {
		$provinceMap[$code] = $province;
		continue;
	}

	$cityFlag = substr($code, -3);
	if ($cityFlag != '000' && $chinaFlag == '156') {
		$cityMap[$code] = $city;
	}
}

$provinceMap = array_flip($provinceMap);
$cityMap  = array_flip($cityMap);

// 解析ip
$default = array(
	'address' => array('未列出的国家或地区', '不限', '不限'),
	'zipcode' => '99900000',
);

$data = array();
$ips = file('ipList.txt');
foreach ($ips as $ipStr) {
	list($ip, $adrStr) = explode('|', $ipStr);
	$ip = trim($ip);
	$adrStr = trim($adrStr);
	$adrSplit = explode("\t", $adrStr);
	foreach ($adrSplit as $k => $v) {
		$adrSplit[$k] = trim($v);
	}

	if (count($adrSplit) != 2 && count($adrSplit) != 3) { // 非法的结构
		continue;
	}

	if (count($adrSplit) == 2) {
		// 国家
		if ($adrSplit[0] == $adrSplit[1]) {
			if (isset($countryMap[$adrSplit[0]])) {
				$data[] = array(
					'ip' => $ip,
					'address' => array($adrSplit[0], '不限', '不限'),
					'zipcode' => $countryMap[$adrSplit[0]]
				);
				continue;
			}

			// 排除骨干网 ip 和名单 ip
			if (!in_array($adrSplit[0], $defulatMap) && (false === strpos($adrSplit[0], '骨干网'))) {
				$data[] = array_merge($default, ['ip' => $ip]);
			}
			continue;
		}

		// 中国省
		if ($adrSplit[0] == '中国' && isset($provinceMap[$adrSplit[1]])) {
			$data[] = array(
				'ip' => $ip,
				'address' => array($adrSplit[0], $adrSplit[1], '不限'),
				'zipcode' => $provinceMap[$adrSplit[1]]
			);
			continue;
		}

		if ($adrSplit[0] != $adrSplit[1]) {
			$data[] = array_merge($default, ['ip' => $ip]);
			continue;
		}
	}

	// 直辖市
	if ($adrSplit[1] == $adrSplit[2] && isset($provinceMap[$adrSplit[1]])) {
		$data[] = array(
			'ip' => $ip,
			'address' => array('中国', $adrSplit[1], '不限'),
			'zipcode' => $provinceMap[$adrSplit[1]],
		);
		continue;
	}

	// 标准地级市
	if (isset($cityMap[$adrSplit[2]])) {
		$data[] = array(
			'ip' => $ip,
			'address' => array('中国', $adrSplit[1], $adrSplit[2]),
			'zipcode' => $cityMap[$adrSplit[2]],
		);
		continue;
	}

	// 非正式地级市
	if (isset($provinceMap[$adrSplit[1]]) && !isset($cityMap[$adrSplit[2]])) {
		$data[] = array(
			'ip' => $ip,
			'address' => array('中国', $adrSplit[1], '不限'),
			'zipcode' => $provinceMap[$adrSplit[1]],
		);
		continue;
	}
	
	echo $ipStr. PHP_EOL;
}

$str = '';
foreach ($data as $value) {
	$value['address'] = implode("-", $value['address']);
	$str .= $value['ip'] . "\t" . $value['address'] . "\t" . $value['zipcode'] .  PHP_EOL;
}
file_put_contents('ipcodeList.txt', $str);
