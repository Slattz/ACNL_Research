import copy, base64, requests, urllib3

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

endpoint_url = "https://nasc.nintendowifi.net/ac"

endpoint_headers = {
    'host': 'nasc.nintendowifi.net',
    'X-GameID': '00086201',
    'User-Agent': 'CTR FPD/000C',
    'Content-Type': 'application/x-www-form-urlencoded',
    'Content-Type': 'application/x-www-form-urlencoded'
}

endpoint_certificate = ("./Certificates/ctr-common-1-cert.pem", "./Certificates/ctr-common-1-key.pem")

def nintendo_base64_decode(s):
        return base64.b64decode(s.replace('.', '+').replace('-', '/').replace('*', '='))

def login(login_details):
    login_headers = endpoint_headers
    login_headers['Content-Length'] = str(len(login_details))
    response = requests.post(endpoint_url, headers=login_headers, data=login_details, cert=endpoint_certificate, verify=False)

    login_data = dict(map(lambda a: a.split("="), response.text.split("&")))
    login_data_decoded = copy.copy(login_data)
    for item in login_data_decoded:
	    login_data_decoded[item] = nintendo_base64_decode(login_data_decoded[item])

    login_host, login_port = login_data_decoded['locator'].decode().split(':')
    login_port = int(login_port)

    return {
        'host' : login_host,
        'port' : login_port,
        'token': login_data['token']
    }
