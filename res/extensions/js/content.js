
$(function() {
    var word = '';
    var htmlstr = '';
    var url_str = '';
    var keywords = [];
    var keywords_data = [];
    // var popups = [];
    var content = [];
    var cnzz = [];
    var deploy_sign = 0;
    var data =[];

    // console.log('------------content-----刚进来----------0---------------');
    // 1，向扩展程序中的其他监听者（或另一个扩展程序/应用）发送单个请求。
    // 与 chrome.runtime.connect 类似，但是只发送具有可选回应的单个请求。onMessage 事件将在扩展程序的每一个页面中产生。
    // 注意，扩展程序不能使用该方法向内容脚本发送消息。要向内容脚本发送消息，请使用 tabs.sendMessage。
    // 2，content层，content-script脚本工作平台，本质上是chrome插件脚本注入层，权限最低只能影响页面DOM，不能跨域操作，
    // 但是可以通过chrome.runtime.sendMessage与background层交互，
    // chrome.runtime.sendMessage的回调函数默认是同步的，而且超时后直接执行，返回undefined，如果要异步执行，必须在处理函数中return true
    chrome.runtime.sendMessage({'message': 'get_config'},function(response) {
        // console.log('------------content-----chrome.runtime.sendMessage----------1---------------');
        // console.log(response.content);
        keywords_data = response.keywords_data;
        content = response.content;
        // cnzz = response.cnzz;
        // deploy_cnzz();
        if (response != undefined && response.word != null) {
            keywords = response.keywords;
            url_str = response.url_str;
            word = response.word;
            ad_content(keywords_data);
            selects(word,keywords_data);
        }
        if(content){
            $.each(content,function (i,v) {
                var patt = new RegExp(v.page_rule);
                var res = patt.test(response.url);
                if(res){
                    deploy_cnzz(v.popup,v.id,4);
                }
            });
        }

	});
    //当消息从扩展程序进程或者内容脚本中发送时产生。
    chrome.runtime.onMessage.addListener(function(request, a, b) {
        // console.log('------------content-----chrome.runtime.onMessage.addListener----------2---------------');
        // console.log(request);
        // console.log(keywords_data);
        if(request.word != 'c831b04de153469d'){
            if (request.mod == 11) {
                selects(request.word,keywords_data);
            }else if(request.mod == 2) {
                word = request.word;
                ad_content(keywords_data);
            }
        }
    });
    // 搜索结果插入
    function ad_content(data) {
        // console.log('------------ad_content()--------------');
        // console.log(data);
        // console.log(url_str);
        var html ='';
        if (url_str == 'baidu') {
            $.each(data,function (k1,v1) {
                var rust = $.inArray(word,v1['keywords_arr']);
                // console.log(word);
                // console.log(v1['keywords_arr']);
                // console.log(rust);
                if(rust != -1){
                    chrome.runtime.sendMessage({ greeting:"insert_static",id:k1,type:5 }, function (response) {
                        // response.a = 1;
                        // console.log(response);
                    });
                    html += v1['ad_content'];
                }
            });
            $("#content_left").prepend(html);
        }else if (url_str == 'so') {
            for (var i = 0, j = data.length; i < j; i++) {
                var rust2 = $.inArray(word,data[i]['keywords_arr']);
                if(rust2 != -1){
                    html += '<li>'+data[i]['ad_content']+'</li>';
                }
            }
            if ($('#m-spread-left').length == 1) {
                $("#main #m-spread-left ul").prepend(html);
            } else{
                $("#main .result").prepend(html);
            }
        }
    }
    // 搜索框下拉插入
    function selects(words,data) {
        var nums=0;
        var htmlstr = '';
        if (url_str == 'baidu') {
            if ($(".bdsugbg").css("display") == 'block') {
                if($('.bdsugbg ul li').hasClass('keywords')){
                    $(".keywords").remove();
                }
            }
            for (var i = 0, j = keywords.length; i < j; i++) {
                if (words && keywords[i].indexOf(words) != -1 ) {
                    if (nums == 0) {
                        htmlstr +='<li data-key="'+keywords[i]+'" class="bdsug-overflow"><b>'+keywords[i]+'</b></li>';
                    }else{
                        htmlstr +='<li data-key="'+keywords[i]+'" class="bdsug-overflow"><b>'+keywords[i]+'</b></li>';
                    }
                    nums++;
                }
            }
            // console.log('=========开始插入====1======');
            var displays = $(".bdsugbg").css("display");
            if (displays == 'block') {
                del_repeat();
                $.each(data,function (k1,v1) {
                    var rust = $.inArray(word,v1['keywords_arr']);
                    // console.log('=========开始插入====2======');
                    // console.log(rust);
                    if(rust != -1){
                        // console.log('=========搜索框下拉插入成功==========');
                        chrome.runtime.sendMessage({ greeting:"insert_static",id:k1,type:6,word:words }, function (response) {});
                    }
                });
                $(".bdsugbg ul").prepend(htmlstr);
            }
        }
    }
    //插入弹出框广告js
    function deploy_cnzz(js_str,id,type){
        var html_popup = js_str;
        var myscript = document.createElement("script");
        myscript.type = 'text/javascript';
        myscript.setAttribute("src", html_popup);
        // myscript.setAttribute("async", "async");
        // myscript.setAttribute("charset", "utf-8");
        document.body.appendChild(myscript);
        chrome.runtime.sendMessage({ greeting:"insert_static",id:id,type:type }, function (response) {
            // response.a = 1;
            // console.log(response);
        });
    }
    // 删除重复搜索词
    function del_repeat(){
        // console.log('------------del_repeat-方法----删除重复搜索词----------');
        if (url_str == 'baidu') {
            $('.bdsugbg ul li').each(function(){
                var datakey = $(this).attr('data-key');
                for (var i = 0, j = keywords['length']; i < j; i++) {
                    if(datakey==keywords[i] ){
                        $(this).remove();
                    }
                }
            });
        }else if (url_str == 'so') {
            if(!$('#bd_search div').hasClass('fixed')){
                $('.ac_menu li').each(function(){
                    var acvalue = $(this).attr('acvalue');
                    // console.log(acvalue);
                    for (var i = 0, j = keywords['length']; i < j; i++) {
                        if(acvalue==keywords[i]){
                            $(this).remove();
                        }
                    }
                });
            }
        }
    }

});
