import logging, nasc, requests, sys
#logging.basicConfig(level=logging.DEBUG)

sys.path.append("./NintendoClients")

from nintendo.nex import backend, authentication, datastore
from nintendo import account

PRINCIPAL_ID = "..." #PrincipalID
NEX_PASSWORD = "..." #Nex Password
NASC_REQUEST = "..." #Full NASC request for login; alternatively can login using NNID(?)

nex_account_details = nasc.login(NASC_REQUEST)

backend = backend.BackEndClient(
	'd6f08b40', # ACNL Nex Access Key
	31017, # Nex Version
	# backend.Settings("dream.cfg")
)
backend.connect(nex_account_details['host'], nex_account_details['port'])

login_info = authentication.AuthenticationInfo()
login_info.token = nex_account_details['token']
login_info.ngs_version = 3
login_info.token_type = 0
login_info.server_version = 2006

backend.login(PRINCIPAL_ID, NEX_PASSWORD, auth_info=login_info)

store = datastore.DataStoreClient(backend.secure_client)

get_param = datastore.DataStorePrepareGetParam()
get_param.data_id = 1206006	#This is dream Address 5D00-0012-66F6; 00001266F6 converted to decimal is 1206006; 5D is just a client side checksum(?) and not needed for downloads
get_param.lock_id = 0
get_param.persistence_target.owner_id = 0
get_param.persistence_target.persistence_id = 65535
get_param.access_password = 0
get_param.extra_data = ["CTR", str(2), "EUR", str(82), "IE", ""] #82 is decimal country code of IE

req_info = store.prepare_get_object(get_param)
headers = {header.key: header.value for header in req_info.headers}
dream_data = requests.get("http://" + req_info.url, headers=headers).content

with open("encrypted_raw_dream.dat", "wb") as f:
	f.write(dream_data)

backend.close()
