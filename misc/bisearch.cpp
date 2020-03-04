ll Bisearch(ll ok, ll ng, function<bool(ll)> func){
    while(std::abs(ok-ng)>1){
        //cout << ok << " " << ng << endl;
        ll mid = (ok+ng)/2;
        if(func(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}

auto iter = std::partition_point(a.begin(), a.end(), func);